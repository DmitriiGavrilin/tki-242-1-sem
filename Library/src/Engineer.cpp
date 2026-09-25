#include "Engineer.h"
#include <sstream>
#include <utility>
namespace miit::domain {
Engineer::Engineer(int id, const std::string& name, const std::string& category, const std::string& owner,
                     const std::string& reference, const std::string& location, std::vector<std::string> tags,
                     double price, int quantity, int day, bool active,
                     const std::string& detail)
    : DepartmentWorker(id, name, category, owner, reference, location, std::move(tags), price, quantity, day, active), detail_(detail) {}
std::string Engineer::type() const { return "Engineer"; }
std::string Engineer::info() const {
    std::ostringstream out;
    out << type() << ": " << name() << ", category=" << category() << ", owner=" << owner()
        << ", reference=" << reference() << ", location=" << location()
        << ", price=" << price() << ", quantity=" << quantity() << ", detail=" << detail_;
    return out.str();
}
const std::string& Engineer::detail() const noexcept { return detail_; }
}
