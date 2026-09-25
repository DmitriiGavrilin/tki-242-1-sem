#include "DepartmentWorker.h"
#include <algorithm>
#include <stdexcept>
#include <utility>
namespace miit::domain {
DepartmentWorker::DepartmentWorker(int id, const std::string& name, const std::string& category, const std::string& owner,
               const std::string& reference, const std::string& location, std::vector<std::string> tags,
               double price, int quantity, int day, bool active)
    : id_(id), name_(name), category_(category), owner_(owner), reference_(reference), location_(location), tags_(std::move(tags)),
      price_(price), quantity_(quantity), day_(day), active_(active) {
    if (id < 0 || price < 0.0 || quantity < 0) throw std::invalid_argument("Negative record value");
}
DepartmentWorker::~DepartmentWorker() = default;
int DepartmentWorker::id() const noexcept { return id_; }
const std::string& DepartmentWorker::name() const noexcept { return name_; }
const std::string& DepartmentWorker::category() const noexcept { return category_; }
const std::string& DepartmentWorker::owner() const noexcept { return owner_; }
const std::string& DepartmentWorker::reference() const noexcept { return reference_; }
const std::string& DepartmentWorker::location() const noexcept { return location_; }
const std::vector<std::string>& DepartmentWorker::tags() const noexcept { return tags_; }
double DepartmentWorker::price() const noexcept { return price_; }
int DepartmentWorker::quantity() const noexcept { return quantity_; }
int DepartmentWorker::day() const noexcept { return day_; }
bool DepartmentWorker::active() const noexcept { return active_; }
bool DepartmentWorker::hasTag(const std::string& tag) const { return std::find(tags_.begin(), tags_.end(), tag) != tags_.end(); }
void DepartmentWorker::changeQuantity(int delta) {
    if (quantity_ + delta < 0) throw std::invalid_argument("Quantity cannot become negative");
    quantity_ += delta;
}
}
