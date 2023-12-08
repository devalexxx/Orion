//
// Created by Alex on 05/12/2023.
//

#ifndef ORION_ARCHIVE_H
#define ORION_ARCHIVE_H

#include <vector>

namespace orion {

    class Archive {
    public:
        template<typename Data>
        friend Archive& operator<<(Archive& archive, const Data& data);
    private:
        std::vector<uint8_t> m_data;
    };

} // orion

#endif //ORION_ARCHIVE_H
