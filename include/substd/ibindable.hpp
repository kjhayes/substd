#ifndef SUBSTD_IBINADABLE_HPP
#define SUBSTD_IBINDABLE_HPP

namespace ss{

template<class self>
class IBindable {
private:
    static IBindable<self>* currently_active = nullptr;
public:
    void SmartBind(){
        if(this != currently_active){
            this = currently_active;
            Bind();
        }
    }
    virtual void Bind() = 0;
};

}

#endif