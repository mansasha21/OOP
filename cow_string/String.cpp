#include "String.hpp"
#include <iostream>
#include <cstring>
#include <algorithm>

namespace {
	bool exist(const char*where, const char* what) {
		int sz_a = strlen(where);
		int sz_b = strlen(what);
		for (int i = 0; i < sz_a; i++) {
			if (where[i] != what[i])
				return false;
			if (i + 1 == sz_b)
				return true;
		}
		return sz_b == sz_a;
	}
}
String::String() : data_(new char), size_(0), capacity_(1), use_count_(new size_t) {
	data_[0] = '\0';
	*use_count_ = 1;
}

String::String(const char* str):String() {
	if (str) {
		delete[] data_;
		size_ = strlen(str);
		data_ = new char[size_ + 1];
		memcpy(data_, str, size_ + 1);
		capacity_ = size_ + 1;
	}	
}

String::String(const char* str, size_t n):String() {
	if (str) {
		delete[] data_;
		int size = std::min(strlen(str), n);
		size_ = size;
		capacity_ = size + 1;
		data_ = new char[capacity_];
		memcpy(data_, str, size);
		data_[size_] = '\0';
	}
}

String::String(size_t n, char c) {
	use_count_ = new size_t;
	*use_count_ = 1;
	size_ = n;
	capacity_ = n + 1;
	data_ = new char[capacity_];
	memset(data_, c, n);
	data_[size_] = '\0';
}

String::String(const String& str) {
	data_ = str.data_;
	size_ = str.size_;
	capacity_ = str.capacity_;
	use_count_ = str.use_count_;
	*use_count_ = *use_count_ + 1;
}

String::String(const String& str, size_t pos, size_t len) {
	if (pos > str.size_) {
		throw std::out_of_range("Position greater then size");
	}
	use_count_ = new size_t;
	*use_count_ = 1;
	size_ = std::min(str.size_-pos, len);
	capacity_ = size_+1;
	data_ = new char[capacity_];
	memcpy(data_, str.data_ + pos,size_);
	data_[size_] = '\0';
}

String:: ~String() {
	if (*use_count_ > 1) {
		*use_count_ = *use_count_ - 1;
		return;
	}
	delete[]data_;
	delete use_count_;
}

size_t String::size() const {
	return size_;
}

size_t String::capacity() const {
	return capacity_;
}

void String::reserve(size_t n) {
	if (n <= capacity_) return;
	char* new_data = new char[n];
	memcpy(new_data, data_, size_+1);
	size_t size = size_;
	if (*use_count_ > 1) {
		*this = String();
	}
	size_ = size;
	capacity_ = n;
	delete[] data_;
	data_ = new_data;
}

void String::clear() {
	if (size_ == 0)
		return;
	if (*use_count_ > 1) {
		*this = String();
	}
	size_ = 0;
}

bool String::empty() const {
	return size_ == 0;
}

char& String::at(size_t pos) {
	if (pos >= size_) {
		throw std::out_of_range("Position greater or equal then size");
	}
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	return data_[pos];
}

const char& String::at(size_t pos) const {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	return data_[pos];
}

char& String::operator[](size_t pos) {
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	return data_[pos];
}
const char& String::operator[](size_t pos) const {
	return data_[pos];
}

char& String::back() {
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	return size_ > 0 ? data_[size_ - 1] : data_[0];
}
const char& String::back() const {
	return size_ > 0 ? data_[size_ - 1] : data_[0];
}

char& String::front() {
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	return data_[0];
}
const char& String::front() const {
	return data_[0];
}

String& String::operator+=(const String& str) {
	*this += str.data_;
	return *this;
}

String& String::operator+=(const char* str) {
	if (!str||str[0]=='\0')
		return *this;
	int sz_str = strlen(str);
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	if(size_+sz_str < capacity_){
		strcat_s(data_,capacity_,str);
		size_ += sz_str;
	}
	else {
		char* new_data = new char[sz_str + size_+1];
		memcpy(new_data, data_, size_);
		new_data[size_] = '\0';
		strcat_s(new_data, sz_str + size_ + 1,str);
		delete[] data_;
		data_ = new_data;
		capacity_ = sz_str +size_+1;
		size_ += sz_str;
	}
	return *this;
}

String& String::operator+=(char c) {
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	if ((int)size_ < (int)capacity_ - 1) {
		data_[size_] = c;
		data_[size_ + 1] = '\0';
		size_++;
	}
	else {
		char* new_data = new char[capacity_+10];
		memcpy(new_data, data_, ++size_);
		new_data[size_-1] = c;
		new_data[size_] = '\0';
		capacity_ += 10;
		delete[] data_;
		data_ = new_data;
	}
	return *this;
}
String& String::operator=(const String& str) {
	if (str.use_count_ == use_count_) {
		return *this;
	}
	if (*use_count_ > 1) {
		*use_count_ -= 1;
	}
	else {
		delete use_count_;
		delete[] data_;
	}
	use_count_ = str.use_count_;
	*use_count_ += 1;
	size_ = str.size_;
	capacity_ = str.capacity_;
	data_ = str.data_;
	return *this;
}

String& String::operator=(const char* str) {
	if (!str) {
		*this = String();
	}
	else {
		*this = String(str);
	}
	return *this;
}

String& String::insert(size_t pos, const String&  str) {
	insert(pos, str.data_);
	return *this;
}

String& String::insert(size_t pos, const char* str) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	if (!str||str[0]=='\0') {
		return *this;
	}
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	size_t sz_str = strlen(str);
	if (sz_str + size_ < capacity_) {
		memmove(data_ + pos + sz_str, data_ + pos, size_+1-pos);
		memcpy(data_ + pos, str, sz_str);
	}
	else {
		char* new_data = new char[sz_str + capacity_];
		memcpy(new_data, data_, pos);
		memcpy(new_data + pos, str, sz_str);
		memcpy(new_data + sz_str + pos, data_ + pos, capacity_ - pos);
		delete[] data_;
		data_ = new_data;
		capacity_ += sz_str;
	}
	size_ += sz_str;
	return *this;
}

String& String::insert(size_t pos, size_t n, char c) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	if (c == '\0') {
		if (n + size_ < capacity_) {
			memmove(data_ + pos + n, data_ + pos, size_ + 1 - pos);
			memset(data_ + pos, c, n);
		}
		else {
			char* new_data = new char[n + capacity_];				//check it
			memcpy(new_data, data_, pos);
			memset(new_data + pos, c, n);
			memcpy(new_data + n + pos, data_ + pos, capacity_ - pos);
			delete[] data_;
			data_ = new_data;
			capacity_ += n;
		}
		size_ += n;
		return *this;
	}
	char* str = new char[n + 1];
	memset(str, c, n);
	str[n] = '\0';
	insert(pos, str);
	delete[] str;
	return *this;
}

String& String::erase(size_t pos, size_t len) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	size_t ndata_sz=0;
	if (len == npos)
		ndata_sz = pos;
	else
		ndata_sz = pos + len > size_ ? pos : size_ - len;
	memmove(data_ + pos, data_ + size_ + pos - ndata_sz, ndata_sz + 1 - pos);
	size_ = ndata_sz;
	return *this;
}

String& String::replace(size_t pos, size_t len, const String& str) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	replace(pos, len, str.data_);
	return *this;
}

String& String::replace(size_t pos, size_t len, const char* str) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	if (*use_count_ > 1) {
		*this = String(data_);
	}
	if (!str)
		return *this;
	size_t nsz;
	size_t str_size = strlen(str);
	if (len == npos||len+pos>size_)
		nsz = pos+str_size;
	else
		nsz = size_+ str_size -len;
	if (nsz < capacity_) {
		memmove(data_ + pos + str_size, data_ + pos + size_ + str_size - nsz, nsz - str_size - pos + 1);
		memcpy(data_ + pos, str, str_size);
	}
	else {
		char* ndata = new char[nsz + 1];
		memcpy(ndata, data_, pos);
		memcpy(ndata + pos, str, str_size);
		if (len + pos <= size_)
			memcpy(ndata + pos + str_size, data_ + pos + len, size_ - pos - len);
		ndata[nsz] = '\0';
		delete[] data_;
		data_ = ndata;
		capacity_ = nsz + 1;
	}
	size_ = nsz;
	return *this;
}

String& String::replace(size_t pos, size_t len, size_t n, char c) {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	size_t nsz;
	if (len == npos || len + pos > size_)
		nsz = pos + n;
	else
		nsz = size_ + n - len;
	if (nsz < capacity_) {
		memmove(data_ + pos + n, data_ + pos + size_ + n - nsz, nsz - n - pos + 1);
		memset(data_ + pos, c, n);
		size_ = nsz;
	}
	else {
		char *str = new char[n + 1];
		memset(str, c, n);
		str[n] = '\0';
		replace(pos, len, str);
		delete[] str;
	}
	return *this;
}

void String::swap(String& str) {
	std::swap(*this, str);
}

const char* String::data()const {
	return data_;
}

size_t String::find(const String& str, size_t pos) const {
	if (pos > size_)
		return npos;
	return find(str.data_, pos);
}

size_t String::find(const char* str, size_t pos) const {
	if (pos > size_ || !str)
		return npos;
	bool same;
	for (size_t i = pos; i < size_; i++) {
		same = exist(data_ + i, str);
		if (same)
			return i;
	}
	return npos;
}

size_t String::find(char c, size_t pos) const {
	if (pos > size_)
		return npos;
	return find(&c, pos);
}

String String::substr(size_t pos, size_t len) const {
	if (pos > size_) {
		throw std::out_of_range("Position greater then size");
	}
	if (pos == size_) {
		return String();
	}

	size_t nsize;
	if (len == npos)
		nsize = size_ - pos;
	else
		nsize = pos + len > size_ ? size_ - pos : len;
	
	return String(data_ + pos, nsize);
}

int String::compare(const String& str)const {
	return compare(str.data_);
}

int String::compare(const char* str)const {
	if (!str)
		return 1;
	size_t str_size = strlen(str);
	size_t cmp_sz = str_size > size_ ? size_ : str_size;
	for (size_t i = 0; i < cmp_sz; i++) {
		if (data_[i] == str[i])
			continue;
		else if (data_[i] < str[i])
			return 1;
		else
			return -1;
	}
	if (str_size > size_)
		return 1;
	else if (str_size < size_)
		return -1;
	else 
		return 0;
}

size_t String::countRef()const {
	return *use_count_;
}
