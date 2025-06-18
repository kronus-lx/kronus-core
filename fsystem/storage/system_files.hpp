#pragma once

#include <mutex>
#include <vector>
#include <memory>
#include <type_traits>

namespace fs = std::filesystem;

namespace fsystem {
    namespace storage {
        template <
            class CharT, 
            typename SizeT = size_t, 
            typename NameT = std::string
        >
        requires (std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>)
        class AbstractFile {
        protected:
            using Path = std::basic_string<CharT>;
            using Buffer = std::vector<CharT>;
            using Name = NameT;
        public:
            virtual std::unique_ptr<AbstractFile>clone() const = 0;
            virtual void reset(std::string_view system_path) = 0;
            virtual bool exists() const = 0;
            virtual SizeT size() const noexcept = 0;
            virtual const Path& path() const noexcept = 0;
            virtual void clear() = 0;
            virtual Name name() const = 0;
            virtual void set_fname(Name name) = 0;
            virtual ~AbstractFile() = default;
        };

        template<class T>
        class Collection {
        protected:
            using element_collection= std::vector<std::unique_ptr<T>>;
        public:
            virtual ~Collection() = default;
        };

        namespace futils {
            class File : public AbstractFile<char, size_t> {
            protected:
                using c_type = char;
            private:
                Path systemPath;
                Buffer fcontents;
                Name fname;
            public:
                /**
                 * @brief Default constructor for File.
                 * Initializes an empty file with no path, contents, or name.
                 */
                File() noexcept : systemPath(""), fcontents({}), fname("") {}

                /**
                 * @brief Copy constructor for File.
                 * Creates a new File by copying the path, contents, and name of another File.
                 * @param other The File to copy from.
                 */
                File(const File& other) noexcept
                    : systemPath(other.systemPath), fcontents(other.fcontents), fname(other.fname) {
                }

                /**
                 * @brief Constructor for File with content and path.
                 * Initializes a File with the specified content and path, extracting the file name from the path.
                 * @param fcontent The content to initialize the file with.
                 * @param fpath The system path of the file.
                 */
                File(const std::string& fcontent, const std::string& fpath)
                    : systemPath(fpath), fcontents(fcontent.begin(), fcontent.end()), fname(fs::path(fpath).filename().string()) {
                }

                /**
                 * @brief Copy assignment operator for File.
                 * Assigns the path, contents, and name of another File to this File.
                 * @param other The File to copy from.
                 * @return Reference to this File.
                 */
                File& operator=(const File& other) noexcept {
                    if (this != &other) {
                        systemPath = other.systemPath;
                        fcontents = other.fcontents;
                        fname = other.fname;
                    }
                    return *this;
                }

                /**
                 * @brief Move constructor for File.
                 * Transfers ownership of the path, contents, and name from another File.
                 * @param other The File to move from.
                 */
                File(File&& other) noexcept
                    : systemPath(std::move(other.systemPath)),
                    fcontents(std::move(other.fcontents)),
                    fname(std::move(other.fname)) {
                }

                /**
                 * @brief Move assignment operator for File.
                 * Transfers ownership of the path, contents, and name from another File.
                 * @param other The File to move from.
                 * @return Reference to this File.
                 */
                File& operator=(File&& other) noexcept {
                    if (this != &other) {
                        systemPath = std::move(other.systemPath);
                        fcontents = std::move(other.fcontents);
                        fname = std::move(other.fname);
                    }
                    return *this;
                }

                
                /**
                 * @brief Creates a deep copy of this File.
                 * @return A unique pointer to the cloned File.
                 */
                std::unique_ptr<AbstractFile<c_type>> clone() const override {
                    return std::make_unique<File>(*this);
                }

                /**
                 * @brief Returns the size of the file's contents.
                 * @return The number of characters in the file's contents.
                 */
                size_t size() const noexcept override {
                    return fcontents.size();
                }

                /**
                 * @brief Checks if the file exists in the filesystem.
                 * @return True if the file has a non-empty path and exists, false otherwise.
                 */
                bool exists() const override {
                    return !systemPath.empty() && fs::exists(systemPath);
                }

                /**
                 * @brief Resets the file to a new system path.
                 * Clears contents and updates the path and name to the specified path.
                 * @param system_path The new system path.
                 */
                void reset(std::string_view system_path) override {
                    systemPath = system_path;
                    fcontents.clear();
                    fname = fs::path(system_path).filename().string();
                }

                /**
                 * @brief Returns the file's system path.
                 * @return Const reference to the file's path.
                 */
                const Path& path() const noexcept override {
                    return systemPath;
                }

                /**
                 * @brief Clears the file's contents, path, and name.
                 */
                void clear() override {
                    fcontents.clear();
                    fname.clear();
                    systemPath.clear();
                }

                /**
                 * @brief Returns the file's name.
                 * @return The name of the file.
                 */
                Name name() const override {
                    return fname;
                }

                /**
                 * @brief set_fnames the file.
                 * Updates the file's name to the specified value.
                 * @param name The new name for the file.
                 */
                void set_fname(Name name) override {
                    fname = name;
                }

                ~File() = default;
            };

            class Files : public Collection<AbstractFile<char>> {
            protected:
                using FileCollection = element_collection;
                using FileReference = std::unique_ptr<File>;
            private:
                FileCollection files;
                struct Mutex {
                    using Mx = std::mutex;
                    mutable Mx mx;
                } Mut;
            public:
                /**
                 * @brief Default constructor for Files.
                 * Initializes an empty collection of files.
                 */
                Files() = default;

                /**
                 * @brief Copy constructor for Files.
                 * Creates a new Files collection by cloning all files from another collection.
                 * @param files The Files collection to copy from.
                 */
                Files(const Files& files) {
                    std::scoped_lock lk(this->Mut.mx, files.Mut.mx);
                    for (const auto& file : files.files) {
                        this->files.emplace_back(file->clone());
                    }
                }

                /**
                 * @brief Copy assignment operator for Files.
                 * Assigns a new collection by cloning all files from another collection.
                 * @param files The Files collection to copy from.
                 * @return Reference to this Files collection.
                 */
                Files& operator=(const Files& files) {
                    if (this != &files) {
                        std::scoped_lock lk(this->Mut.mx, files.Mut.mx);
                        FileCollection temp;
                        for (const auto& file : files.files) {
                            temp.emplace_back(file->clone());
                        }
                        this->files = std::move(temp);
                    }
                    return *this;
                }

                /**
                 * @brief Move constructor for Files.
                 * Transfers ownership of the files collection from another Files object.
                 * @param files The Files collection to move from.
                 */
                Files(Files&& files) noexcept {
                    std::lock_guard<Mutex::Mx> lk(files.Mut.mx);
                    this->files = std::move(files.files);
                }

                /**
                 * @brief Move assignment operator for Files.
                 * Transfers ownership of the files collection from another Files object.
                 * @param files The Files collection to move from.
                 * @return Reference to this Files collection.
                 */
                Files& operator=(Files&& files) noexcept {
                    if (this != &files) {
                        std::scoped_lock lk(this->Mut.mx, files.Mut.mx);
                        this->files = std::move(files.files);
                    }
                    return *this;
                }

                /**
                 * @brief Adds a file to the collection.
                 * Clones the specified file and adds it to the collection.
                 * @param file The File to add.
                 */
                void add(File& file) noexcept {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    files.emplace_back(std::make_unique<File>(file));
                }

                /**
                 * @brief Retrieves a file at the specified index.
                 * @param index The index of the file to retrieve.
                 * @return A unique pointer to a clone of the file.
                 * @throws std::out_of_range If the index is out of range.
                 */
                FileReference get(unsigned int index) const {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    if (index < 0 || index >= files.size()) {
                        throw std::out_of_range("Index out of range");
                    }
                    return FileReference(static_cast<File*>(files[index]->clone().release()));
                }

                /**
                 * @brief Retrieves a clone of the file at the specified index.
                 * @param index The index of the file to retrieve.
                 * @return A unique pointer to the cloned file.
                 * @throws std::out_of_range If the index is out of range.
                 */
                FileReference clone(unsigned int index) const {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    if (index < 0 || index >= files.size()) {
                        throw std::out_of_range("Index out of range");
                    }
                    return FileReference(static_cast<File*>(files[index]->clone().release()));
                }

                /**
                 * @brief Clears all files from the collection.
                 */
                void clear() noexcept {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    files.clear();
                }

                /**
                 * @brief Returns the number of files in the collection.
                 * @return The number of files in the collection.
                 */
                std::size_t count() const noexcept {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    return files.size();
                }

                /**
                 * @brief Removes a file at the specified index.
                 * @param index The index of the file to remove.
                 * @throws std::out_of_range If the index is out of range.
                 */
                void remove(unsigned int index) {
                    std::lock_guard<Mutex::Mx> lk(Mut.mx);
                    if (index < 0 || index >= files.size()) {
                        throw std::out_of_range("Index out of range");
                    }
                    files.erase(files.begin() + index);
                }

                /**
                 * @brief Merges another Files collection into this one.
                 * Clones all files from the other collection and appends them to this collection.
                 * @param files The Files collection to merge.
                 */
                void merge(const Files& files) {
                    std::scoped_lock lk(this->Mut.mx, files.Mut.mx);
                    for (auto& file : files.files) {
                        this->files.emplace_back(file->clone());
                    }
                }
                ~Files() = default;
            };

            /*
            * 
            */
            
        } // namespace futils
    } // namespace storage
} // namespace fsystem