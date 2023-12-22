<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <!-- <a href="https://github.com/othneildrew/Best-README-Template"> -->
    <img src="https://uploads-ssl.webflow.com/6105315644a26f77912a1ada/63eea844ae4e3022154e2878_Holberton.png" alt="Logo" width="500" height="">
  </a>

  <h3 align="center">Holberton Simple Shell</h3>

  <p align="center">
    A homemade shell 
    <br />
    <a href="https://github.com/BradleyRodriq/holbertonschool-simple_shell/"><strong>Explore the docs »</strong></a>
  </p>
</div>


<!-- ABOUT THE PROJECT -->
## About The Project

A simulation of a linux base shell made with C. Enjoy! :)


</br>


<!-- GETTING STARTED -->
## Getting Started


### Prerequisites
The code was made using C, therefore the only prerequisites will be the compiler gcc (recomended) or a compiler of your preferences.

* If you do not have GCC <a href="https://www.guru99.com/c-gcc-install.html">CLICK HERE!</a> to take you to a Useful guide.

### Installation & Run it
If you want to try the project follow the next steps.


1. Clone the repo

    ```sh
    git clone https://github.com/BradleyRodriq/holbertonschool-simple_shell.git
    ```

2. Compiler command

    ```sh
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
    ```
3. Run _.exec_
    ```sh
    ./hsh
   ```
</br>

<!-- CODE EXPLANATION -->
##  Code
```
// this function loops and waits for user input.
void main(void);

// this function takes the desirable command as a paramater and execute it.
void CMDexe(char *command);

// this function handles SIGINT signal
void handleSIGINT(int signum)

// this function opens the prompt
void open_prompt(void)

// this function executes the command
void runExecve(char *command, char *args[])
```

<!-- CONTACT -->
## Authors
- Brandley A. Rodriguez <bradley.rodriguez2@yahoo.com>
- Jahaziel A. Serrano <serranojahaziel2@gmail.com>
- Luis Rivera <6898@holbertonstudents.com>
