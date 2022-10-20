
### Mandatory Part

- Produce `server` & `client` connection mini architecture
- Simulating mimic - [`bash`](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html) programm
- Send `bash` commands into `server`

### Structures

- `t_table` - Structure of Table which has following members:
    - int   socket_fd;
    - int   connection;
    - int   port;
    - int   type;
    - int   proto;
    - int   client_status;
    - int   socket_status;
    - int   conn_status;
    - char  *cmdline;
    - char  *ip;
    - char  *send;
    - char  *recive;
    - char  *err;
    - char  *warn;

### Created Function

- [`create_table(t_table *, char *, int)`](https://github.com/davitMartirosyan/servershell/blob/master/clientsrc/init.c) - Creates a table structure and initializes socket and connect functions.


