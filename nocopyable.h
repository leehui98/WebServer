#pragma once

class nocopyable{
public:
    nocopyable(const nocopyable&)=delete;
    void operator=(const nocopyable&)=delete;
protected:
    nocopyable()=default;
    ~nocopyable()=default;
};