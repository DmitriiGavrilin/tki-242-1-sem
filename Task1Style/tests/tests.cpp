#include <gtest/gtest.h>
#include "Lecturer.h"
#include "Engineer.h"
#include "Department.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace miit::domain;

std::shared_ptr<Lecturer> makeFirstRecord() {
    return std::make_shared<Lecturer>(1, "Prof Smirnov", "lecturer", "Software Dept", "reference-a", "location A", std::vector<std::string>{"common", "research"}, 100.0, 10, 10, true, "primary record");
}

std::shared_ptr<Engineer> makeSecondRecord() {
    return std::make_shared<Engineer>(2, "Alex Morozov", "engineer", "Lab", "reference-b", "location B", std::vector<std::string>{"common", "secondary"}, 60.0, 5, 20, false, "secondary record");
}

std::shared_ptr<Lecturer> makeRepeatedRecord() {
    return std::make_shared<Lecturer>(3, "Prof Smirnov", "lecturer", "Software Dept", "reference-a", "location A", std::vector<std::string>{"common", "research", "repeat"}, 100.0, 3, 15, true, "repeated match");
}

Department makeManager() {
    Department manager;
    manager.add(makeFirstRecord());
    manager.add(makeSecondRecord());
    manager.add(makeRepeatedRecord());
    return manager;
}

TEST(DerivedConstructors, FirstDerivedClass) {
    auto record = makeFirstRecord();
    ASSERT_NE(record, nullptr);
    EXPECT_EQ(record->type(), "Lecturer");
}

TEST(DerivedConstructors, SecondDerivedClass) {
    auto record = makeSecondRecord();
    ASSERT_NE(record, nullptr);
    EXPECT_EQ(record->type(), "Engineer");
}

TEST(DomainModel, ConstructorRejectsNegativeId) {
    EXPECT_THROW((Lecturer(-1, "bad", "bad", "bad", "bad", "bad", std::vector<std::string>{}, 1.0, 1, 1, true, "bad")), std::invalid_argument);
}

TEST(DomainModel, ConstructorRejectsNegativePrice) {
    EXPECT_THROW((Lecturer(1, "bad", "bad", "bad", "bad", "bad", std::vector<std::string>{}, -1.0, 1, 1, true, "bad")), std::invalid_argument);
}

TEST(DomainModel, ConstructorRejectsNegativeQuantity) {
    EXPECT_THROW((Lecturer(1, "bad", "bad", "bad", "bad", "bad", std::vector<std::string>{}, 1.0, -1, 1, true, "bad")), std::invalid_argument);
}

TEST(DomainModel, IdGetter) {
    EXPECT_EQ(makeFirstRecord()->id(), 1);
}

TEST(DomainModel, NameGetter) {
    EXPECT_EQ(makeFirstRecord()->name(), "Prof Smirnov");
}

TEST(DomainModel, CategoryGetter) {
    EXPECT_EQ(makeFirstRecord()->category(), "lecturer");
}

TEST(DomainModel, OwnerGetter) {
    EXPECT_EQ(makeFirstRecord()->owner(), "Software Dept");
}

TEST(DomainModel, ReferenceGetter) {
    EXPECT_EQ(makeFirstRecord()->reference(), "reference-a");
}

TEST(DomainModel, LocationGetter) {
    EXPECT_EQ(makeFirstRecord()->location(), "location A");
}

TEST(DomainModel, TagsGetter) {
    const auto record = makeFirstRecord();
    ASSERT_EQ(record->tags().size(), 2U);
    EXPECT_EQ(record->tags().front(), "common");
}

TEST(DomainModel, PriceGetter) {
    EXPECT_DOUBLE_EQ(makeFirstRecord()->price(), 100.0);
}

TEST(DomainModel, QuantityGetter) {
    EXPECT_EQ(makeFirstRecord()->quantity(), 10);
}

TEST(DomainModel, DayGetter) {
    EXPECT_EQ(makeFirstRecord()->day(), 10);
}

TEST(DomainModel, ActiveGetter) {
    EXPECT_TRUE(makeFirstRecord()->active());
    EXPECT_FALSE(makeSecondRecord()->active());
}

TEST(DomainModel, HasTagFindsExistingTag) {
    EXPECT_TRUE(makeFirstRecord()->hasTag("research"));
}

TEST(DomainModel, HasTagRejectsMissingTag) {
    EXPECT_FALSE(makeFirstRecord()->hasTag("missing"));
}

TEST(DomainModel, ChangeQuantityIncreasesValue) {
    auto record = makeFirstRecord();
    record->changeQuantity(3);
    EXPECT_EQ(record->quantity(), 13);
}

TEST(DomainModel, ChangeQuantityDecreasesValue) {
    auto record = makeFirstRecord();
    record->changeQuantity(-3);
    EXPECT_EQ(record->quantity(), 7);
}

TEST(DomainModel, ChangeQuantityRejectsNegativeResult) {
    auto record = makeFirstRecord();
    EXPECT_THROW(record->changeQuantity(-11), std::invalid_argument);
}

TEST(DomainModel, VirtualDestructorWorksThroughBasePointer) {
    std::weak_ptr<DepartmentWorker> observer;
    {
        std::shared_ptr<DepartmentWorker> record = makeFirstRecord();
        observer = record;
        EXPECT_FALSE(observer.expired());
    }
    EXPECT_TRUE(observer.expired());
}

TEST(DerivedTypes, TypeMethodUsesVirtualDispatch) {
    std::shared_ptr<DepartmentWorker> first = makeFirstRecord();
    std::shared_ptr<DepartmentWorker> second = makeSecondRecord();
    EXPECT_NE(first->type(), second->type());
}

TEST(DerivedTypes, InfoMethodUsesVirtualDispatch) {
    std::shared_ptr<DepartmentWorker> first = makeFirstRecord();
    std::shared_ptr<DepartmentWorker> second = makeSecondRecord();
    EXPECT_FALSE(first->info().empty());
    EXPECT_FALSE(second->info().empty());
}

TEST(DerivedTypes, FirstDetailGetter) {
    EXPECT_EQ(makeFirstRecord()->detail(), "primary record");
}

TEST(DerivedTypes, SecondDetailGetter) {
    EXPECT_EQ(makeSecondRecord()->detail(), "secondary record");
}

TEST(DomainManager, DefaultConstructorCreatesEmptyCollection) {
    Department manager;
    EXPECT_TRUE(manager.items().empty());
}

TEST(DomainManager, AddStoresRecord) {
    Department manager;
    manager.add(makeFirstRecord());
    EXPECT_EQ(manager.items().size(), 1U);
}

TEST(DomainManager, ItemsReturnsCompleteCollection) {
    auto manager = makeManager();
    EXPECT_EQ(manager.items().size(), 3U);
}

TEST(DomainManager, FindByNameReturnsAllMatches) {
    auto manager = makeManager();
    EXPECT_EQ(manager.findByName("Prof Smirnov").size(), 2U);
}

TEST(DomainManager, FindByNameReturnsEmptyForMissingValue) {
    auto manager = makeManager();
    EXPECT_TRUE(manager.findByName("missing").empty());
}

TEST(DomainManager, FindByTagReturnsAllMatches) {
    auto manager = makeManager();
    EXPECT_EQ(manager.findByTag("research").size(), 2U);
}

TEST(DomainManager, FindByTagReturnsEmptyForMissingValue) {
    auto manager = makeManager();
    EXPECT_TRUE(manager.findByTag("missing").empty());
}

TEST(DomainManager, AddValidation) {
    Department manager;
    manager.add(nullptr);
    EXPECT_EQ(manager.items().size(), 1U);
}

TEST(ManagerHelpers, FindByCategory) {
    auto manager = makeManager();
    EXPECT_EQ(manager.findByCategory("lecturer").size(), 2U);
    EXPECT_TRUE(manager.findByCategory("missing").empty());
}

TEST(AssignmentOperations, allWorkers) {
    auto manager = makeManager();
    EXPECT_EQ(manager.allWorkers().size(), 3U);
}

TEST(AssignmentOperations, researchProjects) {
    auto manager = makeManager();
    EXPECT_EQ(manager.researchProjects("research").size(), 2U);
    EXPECT_TRUE(manager.researchProjects("missing").empty());
}

TEST(AssignmentOperations, lecturerForClass) {
    auto manager = makeManager();
    EXPECT_EQ(manager.lecturerForClass("lecturer", "research").size(), 2U);
    EXPECT_TRUE(manager.lecturerForClass("lecturer", "missing").empty());
}

TEST(AssignmentOperations, classTypesBySubject) {
    auto manager = makeManager();
    EXPECT_FALSE(manager.classTypesBySubject("Prof Smirnov").empty());
    EXPECT_TRUE(manager.classTypesBySubject("missing").empty());
}

