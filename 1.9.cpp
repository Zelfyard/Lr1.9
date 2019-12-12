#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class MsgError {
private:
	char dataState[255];
public:
	MsgError(const char* errorCode) {
		strcpy(dataState, errorCode);
	}
	char* GetDataState() {
		return dataState;
	}
};

class Buffer
{
	enum IdType
	{
	intBuf,
	doubleBuf,
	charBuf
	}idTipe;
	void* buf = nullptr;
public:
	Buffer();
	Buffer(int);
	Buffer(double);
	Buffer(const char*);
	~Buffer();
	operator int();
	operator double();
	operator char*();
	int operator = (int);
	double operator = (double);
	char* operator = (const char*);
};

void main() 
{
	Buffer buf = 3,buf2 = "pidor";
	int intBuf;
	double doubleBuf;
	char* charBuf = nullptr;
	charBuf = new char[255];
	try
	{
	buf = 23;
	intBuf = buf;
	cout << intBuf<<endl;
	buf = 54.6;
	doubleBuf = buf;
	cout << doubleBuf << endl;
	buf = "Dolbaeb";
	charBuf = buf;
	cout << charBuf << endl;
	}
	catch (MsgError & exception) {
		std::cout << exception.GetDataState();
	}
}

Buffer::Buffer()
{

}

Buffer::Buffer(int buf) :idTipe(intBuf), buf(new int[1])
{
	((int*)this->buf)[0] = buf;
}

Buffer::Buffer(double buf) : idTipe(doubleBuf), buf(new double[1])
{
	((double*)this->buf)[0] = buf;
}

Buffer::Buffer(const char* buf) : idTipe(charBuf),buf(new char[strlen(buf)+2])
{
	strcpy(((char*)this->buf), buf);
}

Buffer::~Buffer()
{
	delete[] buf;
}

Buffer::operator int()
{
	
	switch (idTipe)
	{
	case Buffer::intBuf:
		return ((int*)buf)[0];
		break;
	case Buffer::doubleBuf: 
		throw MsgError("double in int");
		break;
	case Buffer::charBuf:
		throw MsgError("char in int");
		break;
	default:
		break;
	}
}

Buffer::operator double()
{
	switch (idTipe)
	{
	case Buffer::intBuf:
		throw MsgError("int in double");
		break;
	case Buffer::doubleBuf:
		return ((double*)buf)[0];
		break;
	case Buffer::charBuf:
		throw MsgError("char* in double");
		break;
	default:
		break;
	}
	
}

Buffer::operator char* ()
{
	switch (idTipe)
	{
	case Buffer::intBuf:
		throw MsgError("int in char*");
		break;
	case Buffer::doubleBuf:
		throw MsgError("double in char*");
		break;
	case Buffer::charBuf: 
		return (char*)buf;
		break;
	default:
		break;
	}
}

int Buffer::operator=(int buf)
{
	if (this->buf != nullptr && (idTipe == intBuf || idTipe == doubleBuf))
	{
		delete[]this->buf;
		this->buf = nullptr;
	}
	this->buf = (int*)this->buf;
	this->buf = new int[1];
	((int*)this->buf)[0] = buf;
	idTipe=intBuf;
	return ((int*)this->buf)[0];
}

double Buffer::operator=(double buf)
{
	if (this->buf != nullptr && (idTipe == intBuf || idTipe == doubleBuf))
	{
		delete[]this->buf;
		this->buf = nullptr;
	}
	this->buf = (double*)this->buf;
	this->buf = new double[1];
	((double*)this->buf)[0] = buf;
	idTipe = doubleBuf;
	return ((double*)this->buf)[0];
}

char* Buffer::operator=(const char*buf)
{
	if (this->buf != nullptr)
	{
		delete[]this->buf;
		this->buf = nullptr;
	}
	this->buf = (char*)this->buf;
	this->buf = new char[strlen(buf) + 2];
	idTipe = charBuf;
	return strcpy(((char*)this->buf), buf);
}

