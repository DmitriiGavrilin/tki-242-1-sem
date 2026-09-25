#include "Department.h"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>
namespace miit::domain {
void Department::add(std::shared_ptr<DepartmentWorker> item) { items_.push_back(std::move(item)); }
const std::vector<std::shared_ptr<DepartmentWorker>>& Department::items() const noexcept { return items_; }
std::vector<std::shared_ptr<DepartmentWorker>> Department::findByName(const std::string& name) const {
    std::vector<std::shared_ptr<DepartmentWorker>> result;
    for (const auto& item : items_) if (item->name() == name) { result.push_back(item); break; }
    return result;
}
std::vector<std::shared_ptr<DepartmentWorker>> Department::findByTag(const std::string& tag) const {
    std::vector<std::shared_ptr<DepartmentWorker>> result;
    for (const auto& item : items_) if (item->hasTag(tag)) { result.push_back(item); break; }
    return result;
}

std::vector<std::shared_ptr<DepartmentWorker>> Department::findByCategory(const std::string& category) const {
    std::vector<std::shared_ptr<DepartmentWorker>> result;
    for (const auto& item : items_) if (item->category() == category) result.push_back(item);
    return result;
}
std::vector<std::shared_ptr<DepartmentWorker>> Department::allWorkers() const { return items_; }

std::vector<std::shared_ptr<DepartmentWorker>> Department::researchProjects(const std::string& tag) const { return findByTag(tag); }

std::vector<std::shared_ptr<DepartmentWorker>> Department::lecturerForClass(const std::string& category, const std::string& tag) const {
    std::vector<std::shared_ptr<DepartmentWorker>> result;
    for (const auto& item : findByCategory(category)) if (item->hasTag(tag)) result.push_back(item);
    return result;
}

std::vector<std::string> Department::classTypesBySubject(const std::string& name) const { const auto found = findByName(name); return found.empty() ? std::vector<std::string>{} : found.front()->tags(); }
}
