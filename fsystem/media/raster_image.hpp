#pragma once

#include <memory>
#include <fstream>

namespace fsystem
{
    namespace media {

        using MediaBuffer = std::vector<unsigned char>;
        using iMediaStream = std::ifstream;
        using oMediaStream = std::ofstream;

        namespace fs = std::filesystem;

        namespace images {

            class RasterImage {
            private:
                std::unique_ptr<media::MediaBuffer> buffer;

                void init(std::size_t size) {
                    if (!buffer) {
                        buffer = std::make_unique<media::MediaBuffer>(size);
                    }
                    else {
                        buffer->resize(size);
                    }
                }

            public:
                RasterImage() = default;

                RasterImage(const media::MediaBuffer& buffer)
                    : buffer(std::make_unique<media::MediaBuffer>(buffer)) {
                }

                template<typename InputIt>
                RasterImage(InputIt first, InputIt last)
                    : buffer(std::make_unique<media::MediaBuffer>(first, last)) {
                }

                RasterImage(media::MediaBuffer&& buf)
                    : buffer(std::make_unique<media::MediaBuffer>(buf)) {
                }

                RasterImage(media::iMediaStream& stream) {
                    stream.seekg(0, std::ios::end);
                    auto size = static_cast<unsigned int>(stream.tellg());
                    if (size <= 0) {
                        throw std::runtime_error("Error: error initialising media stream");
                    }
                    stream.seekg(0, std::ios::beg);

                    buffer = std::make_unique<media::MediaBuffer>(size);
                    stream.read(reinterpret_cast<char*>(buffer->data()), size);
                    if (stream.fail()) {
                        throw std::runtime_error("Error: Failed to read media stream");
                    }
                }

                void assign(std::size_t size) { init(size); }

                template<Traversable T>
                bool write(const T& path, const char* name) {
                    fs::path systemPath = path + name;

                    fs::create_directories(systemPath.parent_path());

                    media::oMediaStream stream(systemPath, std::ios::out | std::ios::binary);
                    if (!stream)
                        return false;

                    if (buffer && !buffer->empty()) {
                        stream.write(reinterpret_cast<const char*>(buffer->data()), buffer->size());
                        if (stream.fail())
                            return false;
                    }

                    return stream.good();
                }

                size_t size() {
                    return buffer ? buffer->size() : 0;
                }

                ~RasterImage() = default;
            };
        }
    }
}
