#pragma once
#include <string>
#include <vector>
namespace miit::domain {
class DepartmentWorker {
private:
    int id_;
    std::string name_;
    std::string category_;
    std::string owner_;
    std::string reference_;
    std::string location_;
    std::vector<std::string> tags_;
    double price_;
    int quantity_;
    int day_;
    bool active_;
public:
    DepartmentWorker(int id, const std::string& name, const std::string& category, const std::string& owner,
           const std::string& reference, const std::string& location, std::vector<std::string> tags,
           double price, int quantity, int day, bool active);
    virtual ~DepartmentWorker();
    virtual std::string type() const = 0;
    virtual std::string info() const = 0;
    int id() const noexcept;
    const std::string& name() const noexcept;
    const std::string& category() const noexcept;
    const std::string& owner() const noexcept;
    const std::string& reference() const noexcept;
    const std::string& location() const noexcept;
    const std::vector<std::string>& tags() const noexcept;
    double price() const noexcept;
    int quantity() const noexcept;
    int day() const noexcept;
    bool active() const noexcept;
    bool hasTag(const std::string& tag) const;
    void changeQuantity(int delta);
};
}
