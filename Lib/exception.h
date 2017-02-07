/**
    exception.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

class Exception : public std::exception {
	public:
		Exception(const char *text) : type(text) {
		
		}
		
		virtual ~Exception() throw() { }
		
		virtual const char *what() const throw() {
			return type;
		}
		
	private:
		const char *type;
};

#endif //_EXCEPTION_H_
