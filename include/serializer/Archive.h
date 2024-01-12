//
// Created by Alex on 05/12/2023.
//

#ifndef ORION_ARCHIVE_H
#define ORION_ARCHIVE_H

#include "core/type.h"

#include <vector>

namespace orion {

    class Archive {
    public:
        template<typename Data>
        friend Archive& operator<<(Archive& archive, const Data& data);
    private:
        std::vector<u8> m_data;
    };

    template<typename Data>
    Archive &operator<<(Archive &archive, const Data &data) {
        return archive;
    }

} // orion

#endif //ORION_ARCHIVE_H
