#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include<limits>

class User {
private:
    std::string username;
    std::vector<User*> friends;
    std::vector<std::string> posts;

public:
    User(const std::string& username) : username(username) {}

    std::string getUsername() const {
        return username;
    }

    void addFriend(User* user) {
        friends.push_back(user);
    }

    void addPost(const std::string& post) {
        posts.push_back(post);
    }

    void displayPosts() const {
        std::cout << "Posts by " << username << ":\n";
        for (const auto& post : posts) {
            std::cout << post << std::endl;
        }
    }

    void displayFriends() const {
        std::cout << "Friends of " << username << ":\n";
        for (const auto& friendUser : friends) {
            std::cout << friendUser->getUsername() << std::endl;
        }
    }
};

class SocialNetwork {
private:
    std::vector<User*> users;
    std::map<std::string, User*> userMap; // For quick lookup by username

    void loadUsersFromFile() {
        std::ifstream infile("users.txt");
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string username;
            if (!(iss >> username)) { break; }
            addUser(new User(username));
        }
    }

    void saveUsersToFile() {
        std::ofstream outfile("users.txt");
        for (const auto& user : users) {
            outfile << user->getUsername() << std::endl;
        }
    }

public:
    SocialNetwork() {
        loadUsersFromFile();
    }

    ~SocialNetwork() {
        saveUsersToFile();
        for (auto& user : users) {
            delete user;
        }
    }

    void addUser(User* user) {
        users.push_back(user);
        userMap[user->getUsername()] = user;
    }

    User* getUser(const std::string& username) {
        if (userMap.find(username) != userMap.end()) {
            return userMap[username];
        }
        return nullptr;
    }

    void displayAllUsers() const {
        std::cout << "All users:\n";
        for (const auto& user : users) {
            std::cout << user->getUsername() << std::endl;
        }
    }
};

int main() {
    SocialNetwork network;

    while (true) {
        std::cout << "1. Create User\n2. Add Friend\n3. Post Message\n4. Display User Posts\n5. Display User Friends\n6. Display All Users\n7. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 7) break;

        std::string username, friendName, post;

        switch (choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                network.addUser(new User(username));
                break;
            case 2:
                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cout << "Enter friend's username: ";
                std::cin >> friendName;
                {
                    User* user = network.getUser(username);
                    User* friendUser = network.getUser(friendName);
                    if (user && friendUser) {
                        user->addFriend(friendUser);
                    } else {
                        std::cout << "Invalid username or friend name\n";
                    }
                }
                break;
            case 3:
                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter your post: ";
                std::getline(std::cin, post);
                {
                    User* user = network.getUser(username);
                    if (user) {
                        user->addPost(post);
                    } else {
                        std::cout << "Invalid username\n";
                    }
                }
                break;
            case 4:
                std::cout << "Enter username: ";
                std::cin >> username;
                {
                    User* user = network.getUser(username);
                    if (user) {
                        user->displayPosts();
                    } else {
                        std::cout << "Invalid username\n";
                    }
                }
                break;
            case 5:
                std::cout << "Enter username: ";
                std::cin >> username;
                {
                    User* user = network.getUser(username);
                    if (user) {
                        user->displayFriends();
                    } else {
                        std::cout << "Invalid username\n";
                    }
                }
                break;
            case 6:
                network.displayAllUsers();
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
    }

    return 0;
}