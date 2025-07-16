# 💬 Terminal Chat App in C

A simple terminal-based chat system written in C. Users can sign up, log in, create private chats, and exchange messages — all through the command line!

---

## 📦 Features

- ✅ User signup & login
- 💬 One-on-one chat creation
- ✉️ Send and display messages
- 🔒 Login token system (1 user at a time)
- 💾 Dynamic memory (linked list-based storage)
- 🧹 Safe memory cleanup on exit

📝 Usage
Once the app is running, type one of the following commands:

🔐 signup
Create a new user.

Enter Command: signup
Username: alice
Password: 1234

🔓 login
Log into an existing account.

Enter Command: login
Username: alice
Password: 1234

🆕 newChat
Start a new chat with another user.

Enter Command: newChat
Enter chat name: testchat
Enter selected username: bob

🔍 selectChat
Choose which chat to interact with.

Enter Command: selectChat
Enter chat name: testchat

💬 sendMessage
Send a message to the selected chat.

Edit
Enter Command: sendMessage
Enter your message: Hello!

📜 showMessage
View messages in the selected chat.

Enter Command: showMessage
alice: Hello!
bob: Hi!

🚪 logout
Log out from the current session.

Enter Command: logout
Username: alice
Password: 1234
❌ EXIT
Quit the app and free memory.

⚠️ Limitations
No persistent storage (messages disappear after exit)

Only one user and one chat can be active at a time

Max input sizes: 50 characters for usernames, passwords, and messages
