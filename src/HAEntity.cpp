
#include "HAEntity.hpp"
using std::cerr;
using std::endl;

HAEntity::HAEntity(json _state)
{
    cerr << _state.dump();

    state = _state;

    id = state["entity_id"];
    if (state.contains("attributes") && state["attributes"].contains("friendly_name"))
    {
        name = state["attributes"]["friendly_name"];
    }
    else
    {
        name = state["entity_id"];
    }

    domain = this->getDomain();
}

void HAEntity::update(json _state)
{
    state = _state;
}

std::string HAEntity::toString(void)
{
    return state.dump(2);
}

std::string HAEntity::getDomain(void)
{
    auto id = state["entity_id"].get<std::string>();

    // FIXME: boost::split might be nice here, check if its header only?
    auto pos = id.find(".");

    if (pos == std::string::npos)
    {
        throw std::runtime_error("entity ID [" + id + "] contains no period, has no domain?");
    }

    return id.substr(0, pos);
}

HADomain::HADomain(json _state)
{
    state = _state;
}

void HADomain::update(json _state)
{
    state = _state;
}

std::string HADomain::toString(void)
{
    return state.dump(2);
}
