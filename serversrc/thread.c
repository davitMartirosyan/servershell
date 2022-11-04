// #include <pthread.h>
 
// // this program for threads shuld be compiled in folowing manner
// // cc -pthread

// pthead_t thr; //for keeping track of our thread 
// int *pclient = malloc(sizof(int));
// *pclient = client_socket;
// // We need to write everything in pointerr function Exectuion to give it to 
// // thread and execution in it 

// pthread_create(&thr, NULL,&connection_handling, pclient);
 

//  void after_listen(t_table *table)
//  {

//     if(listen(table->socket_server_fd, 3) < 0)
//         table->listening_status = ERR_LISTENING_MSG;
    
//     int client_size = sizeof(client_addr);
//     table->socket_client_fd = accept(table->socket_server_fd, \
//         (struct sockaddr*)&client_addr, \
//         &client_size);

//     if(table->socket_client_fd < 0)
//          table->new_socket_status = ERR_SOCKET_MSG;
    
//  }


// void *connection_handling (int port)
// {
    




//     // //calling some functions 
//     // create_server_table(port);
//     // lexical_analyzer();
//     // token_replacment();
//     // Check_path();
// }