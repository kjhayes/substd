#ifndef SUBSTD_ANIMATION_HPP
#define SUBSTD_ANIMATION_HPP

namespace ss{

template<class T>
struct Frame{
public:
    T data;
    double length;
    Frame():length(1.0){}
    Frame(const T& data, const double& length):data(data),length(length){}
};

template<class T>
class Animation{
private:
    const int size;
    int index;
    double time;
    Frame<T>* frames;
    
public:
    Animation(const int& size):size(size),index(0),time(0.0){
        frames = new Frame<T>[size];
    }
    ~Animation(){
        delete frames;
    }

    bool Tick(double deltatime){
        if(time <= 0.0){
            IncrementFrame(time);
            return true;        
        }
        else{
            time -= deltatime;
            return false;
        }
    }

    T CurrentFrame(){
        return frames[index].data;
    }

    bool IncrementFrame(){
        bool last_frame = IsLastFrame();
        if(last_frame){SetIndex(0);}
        else{index++; time = frames[index].length;}
        return last_frame;
    }
    bool IncrementFrame(const double& time_past){
        bool last_frame = IsLastFrame();
        if(last_frame){
            index = 0; 
        }
        else{
            index++; 
        }
        time = frames[index].length+time_past;
        return last_frame;    
    }
    bool DecrementFrame(){
        bool first_frame = IsFirstFrame();
        if(first_frame){SetIndex(size-1);}
        else{index--; time = frames[index].length;}
        return first_frame;
    }

    bool IsLastFrame(){return (index == (size-1));}
    bool IsFirstFrame(){return (index==0);}

    void SetIndex(const int& index){
        this->index = index; time = frames[index].length;
    }

    void SetFrameData(int ind, Frame<T> frame){
        frames[ind] = frame;
    }
    Frame<T> GetFrameData(int ind){
        return frames[ind];
    }
};

}

#endif