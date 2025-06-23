#include <iostream>
#include <string>
#include <cctype> // for tolower

#include <iostream>
#include <string>
#include <limits> // for cin.ignore
#include "LinkedInManager.hpp"
#include "User.hpp"
#include "Profile.hpp"
#include "Post.hpp"


void displayMenu() {
    std::cout << "\nLinkedIn Demo Menu\n";
    std::cout << "1. Display all users\n";
    std::cout << "2. Display user profile\n";
    std::cout << "3. Add connection\n";
    std::cout << "4. Remove connection\n";
    std::cout << "5. Create post\n";
    std::cout << "6. Like post\n";
    std::cout << "7. Comment on post\n";
    std::cout << "8. Display user connections\n";
    std::cout << "9. Display user posts\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    LinkedInManager linkedin;

    // Pre-populate with some users (optional)
    User* user1 = new User("U001", "abhinavprasad2004ap@gmail.com", "password123");
    User* user2 = new User("U002", "krishnagarg21@gmail.com", "password456");
    Profile* profile1 = new Profile("John Doe", "Software Engineer");
    Profile* profile2 = new Profile("Jane Smith", "Product Manager");
    user1->setProfile(profile1);
    user2->setProfile(profile2);
    linkedin.addUser(user1);
    linkedin.addUser(user2);

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        std::string userId, userId2, content, postId, comment;
        Post* post;
        switch (choice) {
            case 1:
                linkedin.displayAllUsers();
                break;
            case 2:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                linkedin.displayUserProfile(userId);
                break;
            case 3:
                std::cout << "Enter first user ID: ";
                std::getline(std::cin, userId);
                std::cout << "Enter second user ID: ";
                std::getline(std::cin, userId2);
                if (linkedin.addConnection(userId, userId2))
                    std::cout << "Connection added.\n";
                else
                    std::cout << "Failed to add connection.\n";
                break;
            case 4:
                std::cout << "Enter first user ID: ";
                std::getline(std::cin, userId);
                std::cout << "Enter second user ID: ";
                std::getline(std::cin, userId2);
                if (linkedin.removeConnection(userId, userId2))
                    std::cout << "Connection removed.\n";
                else
                    std::cout << "Failed to remove connection.\n";
                break;
            case 5:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                std::cout << "Enter post content: ";
                std::getline(std::cin, content);
                post = linkedin.createPost(userId, content, PostType::TEXT, "2024-01-01");
                if (post)
                    std::cout << "Post created.\n";
                else
                    std::cout << "Failed to create post.\n";
                break;
            case 6:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                std::cout << "Enter post ID: ";
                std::getline(std::cin, postId);
                if (linkedin.likePost(userId, postId))
                    std::cout << "Post liked.\n";
                else
                    std::cout << "Failed to like post.\n";
                break;
            case 7:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                std::cout << "Enter post ID: ";
                std::getline(std::cin, postId);
                std::cout << "Enter comment: ";
                std::getline(std::cin, comment);
                if (linkedin.commentOnPost(userId, postId, comment))
                    std::cout << "Comment added.\n";
                else
                    std::cout << "Failed to add comment.\n";
                break;
            case 8:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                linkedin.displayUserConnections(userId);
                break;
            case 9:
                std::cout << "Enter user ID: ";
                std::getline(std::cin, userId);
                linkedin.displayUserPosts(userId);
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
