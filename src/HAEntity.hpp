
#ifndef HAENTITY_HPP
#define HAENTITY_HPP

#include <nlohmann/json.hpp>
#include <iostream>

using std::map;
using std::string;

using json = nlohmann::json;

class HAEntity
{
public:
  string name;
  string id; 
  string domain;
  HAEntity(void); // do we need this?
  HAEntity(json _state);
  ~HAEntity() {};
  void update(json _state);
  std::string toString(void);

  std::vector<std::string> attrVector(void)
  {
    std::vector<std::string> ret;

    for (const auto &[k, v] : state["attributes"].items())
    {
      ret.push_back(k + std::string(": ") + v.dump());
    }

    return ret;
  }

  std::string getState(void)
  {
    return state["state"];
  }

  json getJsonState(void)
  {
    return state;
  }

  std::string getInfo(void)
  {
    std::ostringstream ret;

    ret << "state=" << getState() << "  ";
    ret << "domain=" << getDomain() << "  ";
    // ret<<""
    return ret.str();
  }


private:
  json state;
  std::string getDomain(void);
};

class HADomain
{
public:
  HADomain(void);
  HADomain(json _state);
  ~HADomain() {};

  void update(json _state);
  std::string toString(void);

  /*
    std::string getState(void)
    {
      return state["state"];
    }
  */

  std::vector<std::string> getServices(void)
  {
    std::vector<std::string> ret;

    // cerr<<state.dump()<<endl;
    for (auto &[service, info] : state.items())
    {
      ret.push_back(service);
    }

    return ret;
  }
private:
  json state;
};

#endif