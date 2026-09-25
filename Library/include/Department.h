#pragma once
#include "DepartmentWorker.h"
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace miit::domain {
class Department {
private:
    std::vector<std::shared_ptr<DepartmentWorker>> items_;
public:
    void add(std::shared_ptr<DepartmentWorker> item);
    const std::vector<std::shared_ptr<DepartmentWorker>>& items() const noexcept;
    std::vector<std::shared_ptr<DepartmentWorker>> findByName(const std::string& name) const;
    std::vector<std::shared_ptr<DepartmentWorker>> findByTag(const std::string& tag) const;

    std::vector<std::shared_ptr<DepartmentWorker>> findByCategory(const std::string& category) const;
    std::vector<std::shared_ptr<DepartmentWorker>> allWorkers() const;
    std::vector<std::shared_ptr<DepartmentWorker>> researchProjects(const std::string& tag) const;
    std::vector<std::shared_ptr<DepartmentWorker>> lecturerForClass(const std::string& category, const std::string& tag) const;
    std::vector<std::string> classTypesBySubject(const std::string& name) const;
};
}
