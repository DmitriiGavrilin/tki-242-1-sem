#pragma once
#include "DepartmentWorker.h"
namespace miit::domain {
class Engineer final : public DepartmentWorker {
private:
    std::string detail_;
public:
    Engineer(int id, const std::string& name, const std::string& category, const std::string& owner,
              const std::string& reference, const std::string& location, std::vector<std::string> tags,
              double price, int quantity, int day, bool active,
              const std::string& detail);
    std::string type() const override;
    std::string info() const override;
    const std::string& detail() const noexcept;
};
}
