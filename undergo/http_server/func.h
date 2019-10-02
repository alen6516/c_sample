struct http_hdr_t {
  char *method;
  char *host;
  char *user_agent;
  char *accept;
};


void *rece_http(void*);
int parse_http(char* buf);
void reply_http();
