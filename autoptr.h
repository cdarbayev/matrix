#ifndef AUTOPTR_H
#define AUTOPTR_H

class Matrix;

class AutoPtr
{
	Matrix* pm;
	bool owner;
public:
	AutoPtr(Matrix* matrix);
	AutoPtr(AutoPtr& other);
	AutoPtr& operator=(AutoPtr& rhs);
	~AutoPtr();
	Matrix* operator->();
};

#endif
