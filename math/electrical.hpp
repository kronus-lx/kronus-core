#pragma once

namespace math
{
    namespace electrical
    {
        enum class OHMS_LAW {
            VOLTAGE,
            CURRENT,
            RESISTANCE
        };

        /**
         * @brief return either V I or R calculation
         * @param type
         * @param input_1
         * @param input_2
         * @return
         */
        double calculateOhmsLaw(OHMS_LAW type, double input_1, double input_2);
    }
}