#include "User.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

User::User(std::string userId, std::string email, std::string password)
    : userId(userId), email(email), password(password), profile(nullptr), active(true) {}

User::~User() {
    delete profile; // profile is owned by User
    // Do NOT delete posts here if posts are managed by LinkedInManager or Post owns itself
    // If posts are only pointers and not owned by User, remove the following loop:
    // for (auto post : posts) { delete post; }
    // Otherwise, if User owns posts, keep it. But in your system, LinkedInManager owns posts.
    // So, remove the following line from User.cpp:
    // for (auto post : posts) { delete post; }
}

std::string User::getUserId() const { return userId; }
std::string User::getEmail() const { return email; }
Profile* User::getProfile() const { return profile; }
bool User::isActive() const { return active; }
const std::vector<User*>& User::getConnections() const { return connections; }
const std::vector<Post*>& User::getPosts() const { return posts; }

void User::setProfile(Profile* profile) {
    delete this->profile;
    this->profile = profile;
}

void User::addConnection(User* user) {
    if (user && user != this &&
        std::find(connections.begin(), connections.end(), user) == connections.end()) {
        connections.push_back(user);
        // Optional: If you want bidirectional connection, uncomment:
        // user->connections.push_back(this);
        // But be careful, this can cause infinite recursion or double connections.
        // In your code, LinkedInManager should handle bidirectional connections.
    }
}

void User::removeConnection(User* user) {
    auto it = std::find(connections.begin(), connections.end(), user);
    if (it != connections.end()) {
        connections.erase(it);
        // Optional: If you want bidirectional removal, uncomment:
        // auto it2 = std::find(user->connections.begin(), user->connections.end(), this);
        // if (it2 != user->connections.end()) {
        //     user->connections.erase(it2);
        // }
        // Again, LinkedInManager should handle this.
    }
}

void User::addPost(Post* post) {
    if (post && std::find(posts.begin(), posts.end(), post) == posts.end()) {
        posts.push_back(post);
    }
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Connections: " << connections.size() << std::endl;
    std::cout << "Posts: " << posts.size() << std::endl;
    if (profile) {
        profile->displayInfo();
    }
}
