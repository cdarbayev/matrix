#include "autoptr.h"
#include "matrix.h"

AutoPtr::AutoPtr(Matrix* matrix)
	:pm(matrix), owner(true)
{}

AutoPtr::AutoPtr(AutoPtr& other)
	:pm(other.pm), owner(other.owner)
{
	other.owner = false;
}

AutoPtr& AutoPtr::operator=(AutoPtr& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	if (this->owner) {
		delete this->pm;
	}
	this->pm = rhs.pm;
	this->owner = rhs.owner;
	rhs.owner = false;
	return *this;
}

AutoPtr::~AutoPtr()
{
	if (owner) {
		delete pm;
	}
}

Matrix* AutoPtr::operator->()
{
	return pm;
}
