#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char UserName[50];
    char Password[50];
    int Token;
    struct User* next;
};
struct Chat {
    char sender[50];
    char message[50];
    struct Chat* next;
};
struct ChatList {
    char ChatName[50];
    char UserOne[50];
    char UserTwo[50];
    int TokenC;
    struct Chat* messages;
    struct ChatList* next;
};
void cleanup(struct User* head, struct ChatList* headL) {
    while (head) {
        struct User* temp = head;
        head = head->next;
        free(temp);
    }

    while (headL) {
        struct ChatList* temp = headL;
        headL = headL->next;

        struct Chat* msg = temp->messages;
        while (msg) {
            struct Chat* msgTemp = msg;
            msg = msg->next;
            free(msgTemp);
        }
        free(temp);
    }
}
struct User* createUser(char* username, char* password) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newUser->UserName, username);
    strcpy(newUser->Password, password);
    newUser->next = NULL;
    return newUser;
}

struct ChatList* createChat(char* UserOne, char* UserTwo, char* ChatName) {
    struct ChatList* newChat = (struct ChatList*)malloc(sizeof(struct ChatList));
    if (newChat == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newChat->ChatName, ChatName);
    strcpy(newChat->UserOne, UserOne);
    strcpy(newChat->UserTwo, UserTwo);
    newChat->next = NULL;
    return newChat;
}
int usernameExists(struct User* head, char* username) {
    struct User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->UserName, username) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int chatExists(struct ChatList* head, char* chatname) {
    struct ChatList* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->ChatName, chatname) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int verifysignup(struct User* head, char* username, char* password) {
    struct User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->UserName, username) == 0 && strcmp(temp->Password, password) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int LoginToken(struct User* head, char* username, char* password) {
    struct User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->UserName, username) == 0 && strcmp(temp->Password, password) == 0) {
            temp->Token = 1;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int LogoutToken(struct User* head, char* username, char* password) {
    struct User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->UserName, username) == 0 && strcmp(temp->Password, password) == 0) {
            temp->Token = 0;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int main() {
    struct User* head = NULL;
    struct ChatList* headL = NULL;
    while (1) {
        char Command[20];
        printf("Enter Command: ");
        scanf("%19s", Command);
        if (strcmp(Command, "signup") == 0) {//signup....
            char username[50];
            char password[50];
            printf("Username: ");
            scanf("%49s", username);
            if (usernameExists(head, username)) {
                printf("Error: Username already exists.\n");
                continue;
            }
            printf("Password: ");
            scanf("%49s", password);
            struct User* newUser = createUser(username, password);
            newUser->next = head;
            head = newUser;
            printf("Signup successful!\n");
        } else if (strcmp(Command, "login") == 0) {//login....
            struct User* temp = head;
            while (temp != NULL) {
                if (temp->Token == 1) {
                    printf("Please logout first.");
                    break;
                }
                temp = temp->next;
            } 
            if (head == NULL) {
                printf("No users available. Please signup first.\n");
                continue;
            }

            char username[50];
            char password[50];
            printf("Username: ");
            scanf("%49s", username);
            printf("Password: ");
            scanf("%49s", password);
            if (verifysignup(head, username, password)) {
                printf("Login successful!\n");
                LoginToken(head, username, password);

            } else {
                printf("Error: Invalid Username or Password.\n");
            }
        } else if (strcmp(Command, "logout") == 0) {//logout....
            if (head == NULL) {
                printf("No users available. Please signup first.\n");
                continue;
            }
            char username[50];
            char password[50];
            printf("Username: ");
            scanf("%49s", username);
            printf("Password: ");
            scanf("%49s", password);
            if (verifysignup(head, username, password)) {
                printf("Logout successful!\n");
                LogoutToken(head, username, password);

            } else {
                printf("Error: Invalid Username or Password.\n");
            }            

        } else if (strcmp(Command, "EXIT") == 0) {//exit....
            printf("Exiting...\n");
            cleanup(head, headL);
            break;

        } else if (strcmp(Command, "newChat") == 0) {
            char username1[50];
            struct User* temp = head;
            int loggedIn = 0;
            while (temp != NULL) {
                if (temp->Token == 1) {
                    strcpy(username1, temp->UserName);
                    loggedIn = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!loggedIn) {
                printf("Error: No user is currently logged in.\n");
                continue;
            }

            char username2[50];
            char chatname[50];
            printf("Enter chat name: ");
            scanf("%49s", chatname);
            if (chatExists(headL, chatname)) {
                printf("Error: Chat already exists.\n");
                continue;
            }

            printf("Enter selected username: ");
            scanf("%49s", username2);
            if (!usernameExists(head, username2)) {
                printf("Error: User '%s' not found.\n", username2);
                continue;
            }
            if (strcmp(username1, username2) == 0) {
                printf("Error: You cannot create a chat with yourself.\n");
                continue;
            }

            struct ChatList* newChat = createChat(username1, username2, chatname);
            newChat->next = headL;
            headL = newChat;
            printf("Chat '%s' created successfully!\n", chatname);
            } else if (strcmp(Command, "selectChat") == 0) {//selectChat

            struct User* temp = head;

            int userLoggedIn = 0;
            while (temp != NULL) {
                if (temp->Token == 1) {
                    userLoggedIn = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!userLoggedIn) {
                printf("Error: No user is currently logged in.\n");
                return 1;
            }
            printf("Enter chat name: ");
            char chatname[50];
            scanf("%49s", chatname);
            struct ChatList* temp1 = headL;
            int chatFound = 0;
            while (temp1 != NULL) {
                if (temp1->TokenC == 1) {
                    temp1->TokenC = 0;
                }
                temp1 = temp1->next;
            }
            temp1 = headL;
            while (temp1 != NULL) {
                if (strcmp(temp1->ChatName, chatname) == 0) {
                    temp1->TokenC = 1;
                    chatFound = 1;
                    printf("Chat '%s' has been selected.\n", chatname);
                    break;
                }
                temp1 = temp1->next;
            }

            if (!chatFound) {
                printf("Error: Chat '%s' not found.\n", chatname);
            }
        } else if (strcmp(Command, "sendMessage") == 0) {//sendMassage
            struct User* temp = head;
            char loggedInUser[50];
            int userLoggedIn = 0;
            while (temp != NULL) {
                if (temp->Token == 1) {
                    strcpy(loggedInUser, temp->UserName);
                    userLoggedIn = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!userLoggedIn) {
                printf("Error: No user is currently logged in.\n");
                continue;
            }
            struct ChatList* chatTemp = headL;
            struct ChatList* selectedChat = NULL;
            while (chatTemp != NULL) {
                if (chatTemp->TokenC == 1) {
                    selectedChat = chatTemp;
                    break;
                }
                chatTemp = chatTemp->next;
            }

            if (selectedChat == NULL) {
                printf("Error: No chat is currently selected.\n");
                continue;
            }
            printf("Enter your message: ");
            char message[50];
            scanf(" %[^\n]s", message);

            struct Chat* newMessage = (struct Chat*)malloc(sizeof(struct Chat));
            if (newMessage == NULL) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(newMessage->sender, loggedInUser);
            strcpy(newMessage->message, message);
            newMessage->next = NULL;
            if (selectedChat->messages == NULL) {
                selectedChat->messages = newMessage;
            } else {
                struct Chat* msgTemp = selectedChat->messages;
                while (msgTemp->next != NULL) {
                    msgTemp = msgTemp->next;
                }
                msgTemp->next = newMessage;
            }

            printf("Message sent successfully!\n");
        } else if (strcmp(Command, "showMessage") == 0) {//showMassage
            struct ChatList* chatTemp = headL;
            struct ChatList* selectedChat = NULL;
            while (chatTemp != NULL) {
                if (chatTemp->TokenC == 1) {
                    selectedChat = chatTemp;
                    break;
                }
                chatTemp = chatTemp->next;
            }
            if (selectedChat == NULL) {
                printf("Error: No chat is currently selected.\n");
                continue;
            }
            if (selectedChat->messages == NULL) {
                printf("No messages in this chat.\n");
                continue;
            }
            struct Chat* msgTemp = selectedChat->messages;
            while (msgTemp != NULL) {
                printf("%s: %s\n", msgTemp->sender, msgTemp->message);
                msgTemp = msgTemp->next;
            }
        } else {
            printf("Error: please enter correct command\n");
        }
    }
}