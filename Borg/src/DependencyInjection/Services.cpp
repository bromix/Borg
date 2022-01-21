#include "Borg/DependencyInjection/Services.h"

namespace Borg::DependencyInjection
{
    std::mutex Services::m_ServicesLock;
    Ref<Detail::Services> Services::m_Services;
}