Mike
Can you rewrite the this program using openssl library base64 or any standard base64 library available on centos  6  or redhat 6
I am getting occasional error I think libb64  is old   
             encode64.c     

I run 
$encode64    filename.gif

Outputs:
Len of base64 string\n
Base64 string\n

Current Makefile    just to show you
$(BINDIR)/encode64: encode64.c
        $(CC) -g $(CFLAGS) encode64.c -L$(LIBDIR) -lb64 -o $(BINDIR)/encode64


Newer version openssl on new server
Might be the latest that redhat supports 
I will check?
But right now this installed

[root@t0168 qfs]# openssl
OpenSSL> version
OpenSSL 1.0.1e-fips 11 Feb 2013
OpenSSL> 