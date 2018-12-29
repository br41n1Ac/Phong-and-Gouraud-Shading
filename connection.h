//
//  connection.h
//  assignment3
//
//  Created by Simon Åkesson on 2018-11-05.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//


#ifndef connection_h
#define connection_h
struct connection {
    int a,b,c;
    connection(): a(0), b(0), c(0) {};
    connection(int x, int y,int z):a(x),b(y),c(z){};
    
};

#endif /* connection_h */
