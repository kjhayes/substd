#ifndef SUBSTD_DOOL_HPP
#define SUBSTD_DOOL_HPP

namespace ss{

struct dool{
protected:
    bool val, change;
public:
    dool();
    dool(const bool&);
    dool(const dool&);

    void Set(const bool&);
    bool GetValue();
    bool IsChanged();
};

}

#endif //GLEWY_DOOL_HPP