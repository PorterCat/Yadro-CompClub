#include "ClubState.hpp"

void ClubState::addToQueue(const std::string& client)
{
    if (clientToIterator.contains(client)) 
        throw std::runtime_error("Duplicate in queue");
    waitingList.push_back(client);
    clientToIterator[client] = std::prev(waitingList.end());
}

std::optional<std::string> ClubState::popFromQueue()
{
    if (waitingList.empty()) return std::nullopt;

    auto client = waitingList.front();
    waitingList.pop_front();
    clientToIterator.erase(client);
    return client;
}

void ClubState::removeFromQueue(const std::string& client)
{
    auto it = clientToIterator.find(client);
    if (it == clientToIterator.end())
        throw std::runtime_error("Client not in queue");
    waitingList.erase(it->second);
    clientToIterator.erase(it);
}

bool ClubState::isQueueFull() const
{
    return waitingList.size() > tables.size() - 1;
}
