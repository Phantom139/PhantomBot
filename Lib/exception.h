/**
    exception.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

class Exception : public exception {
	public:
		Exception(const char *text) : exception(text) {
		
		}
		
		virtual ~Exception() throw() { }
		
		virtual const char *what() const throw() {
			return exception::what();
		}
};

#endif _EXCEPTION_H_
