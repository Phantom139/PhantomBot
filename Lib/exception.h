/**
    exception.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

class Exception : public std::exception {
	public:
		Exception(const char *text) : std::exception(text) {
		
		}
		
		virtual ~Exception() throw() { }
		
		virtual const char *what() const throw() {
			return std::exception::what();
		}
};

#endif _EXCEPTION_H_
