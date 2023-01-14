#pragma once
#include <iostream>
#include <stdexcept>
#include "Item.h"
#include "Course.h"

class Course;

class Student : public Item
{
private:
	std::vector<std::weak_ptr<Course>> courses{}; //заполняем во время update в базе данных

public:
	Student(const std::string& name, size_t id, size_t course, const vector_ids& ids);
	virtual void addItem(std::weak_ptr<Item> item) override;
	const std::vector<std::weak_ptr<Course>>& getCourses() const;
	virtual void serialize(std::ostream& os) override;
};