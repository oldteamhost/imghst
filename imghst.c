#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#if defined(_WIN32)
#include <Windows.h>
#include <winsock2.h>
    #pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#endif

#define VERSION "0.8"
#define MAX_BUF_SIZE 1024

struct grab_options {
    const char* domain;
    const char* protocol;
    const char* user_agent;
    char* path;
    char* format;
    int token_length;
    int count;

    int debug;
    int preset;
};

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t clear_data(void* buffer, size_t size, size_t nmemb, void* userp);
char* generate_random_string(int length);
int delete_file(const char* path);
int download_file(const char* node, const char* out_file, const char* user_agent);
long int get_file_size(const char* file_name);
void parse_config(const char* filename, struct grab_options* gopt);
void delay_ms(int milliseconds);
int check_internet_connection(void);
void help_menu(void);

int main(int argc, char** argv){

    struct grab_options gopt = {
        "",
        "https://",
        "imghst by oldteam",
        "",
        ".png",
        5,
        100
    };

    const char* short_options = "hvc:p:";    
    const struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"count", required_argument, 0, 'c'},
        {"path", required_argument, 0, 'p'},
        {"format", required_argument, 0, 1},
        {"token-length", required_argument, 0, 2},
        {"protocol", required_argument, 0, 3},
        {"user-agent", required_argument, 0, 4},
        {"debug", no_argument, 0, 5},
        {"db", no_argument, 0, 6},
        {"preset", required_argument, 0, 7},
        {"cfg", required_argument, 0, 8},
        {0,0,0,0}
    };

    if (argc <= 1){
        help_menu();
        return 0;
    }

    int rez, option_index = 0;
    int custom_path;
    const char* config_path;

    while((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != EOF){
        switch (rez) {
            case 'h':
                help_menu();
                return 0;
                break;
            case 'v':
                printf("lomaster & oldteam %s\n", VERSION);
                break;
            case 'c':
                gopt.count = atoi(optarg);
                break;
            case 'p':
                gopt.path = optarg;
                custom_path = 1;
                break;
            case 1:
                gopt.format = optarg;
                break;
            case 2:
                gopt.token_length = atoi(optarg);
                break;
            case 3:
                if (strcmp(optarg, "http") == 0){
                    gopt.protocol = "http://";
                }
                else if (strcmp(optarg, "https") == 0){
                    gopt.protocol = "https://";
                }
                else {
                    help_menu();
                    return 0;
                }
                break;
            case 4:
                gopt.user_agent = optarg;
                break;
            case 5:
                gopt.debug = 1;
                break;
            case 6:
                gopt.debug = 1;
                break;
            case 7:
                gopt.preset = 1;
                config_path = optarg;
                break;
            case 8:
                gopt.preset = 1;
                config_path = optarg;
                break;
            case '?':
            default:
                help_menu();
                return 0;
                break;
        }
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now); char datetime[20];

    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", t);

    printf("Starting Imghst %s at %s\n", VERSION, datetime);

    if (check_internet_connection() != 1){
        puts("Cannot connection Internet!");
        exit(1);
    }

    if (optind < argc){
        gopt.domain = argv[optind];
    }

    if (gopt.preset){
        memset(&gopt, 0, sizeof(gopt));
        parse_config(config_path, &gopt);
    }
    
    if (custom_path){
        puts("PATH\t\t\tSTATE\tTIME\tURL");
    }
    else {

        puts("PATH\t\tSTATE\tTIME\tURL");
    }

    int success;

    time_t start_time_full, end_time_full;
    double time_diff_full;

    start_time_full = time(NULL);

    for (int i = 1; i <= gopt.count; i++){
       clock_t start_time, end_time;
       double time_elapsed_ms;

       start_time = clock();

       char* token = generate_random_string(gopt.token_length);
       char* out_file = (char*) malloc(1000);
       out_file[0] = '\0';

       char* result_url = (char*) malloc(100000); 
       result_url[0] = '\0';

       char* file_name = (char*) malloc(1000);
       file_name[0] = '\0';

       strcat(file_name, token);
       strcat(file_name, gopt.format);

       strcat(out_file, gopt.path);

       if (custom_path){
           strcat(out_file, "/");
       }

       strcat(out_file, file_name);

       strcat(result_url, gopt.protocol);
       strcat(result_url, gopt.domain);
       strcat(result_url, "/");
       strcat(result_url,token);
       strcat(result_url, gopt.format);

       int file = download_file(result_url, out_file, gopt.user_agent);
       int file_size = get_file_size(out_file);
       int state, print;

       if (file != 0){
           exit(1);
       }
        
       if (file_size < 100){
           if (gopt.debug != 1){
               delete_file(out_file);
           }
           state = EOF;
       }
       else {
           state = 1;
           success++;
       }

       end_time = clock();
       time_elapsed_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;

       if (state == EOF && gopt.debug == 1){
           printf("%s\tfailed\t%dms\t%s\n", out_file, (int)time_elapsed_ms, result_url);
       }
       if (state == 1){
           printf("%s\tappear\t%dms\t%s\n", out_file, (int)time_elapsed_ms, result_url);
       }


       free(token);
       free(result_url);
    }

    end_time_full = time(NULL);
    time_diff_full = difftime(end_time_full, start_time_full);

    printf("\nImghst done: %d successful in %.1fs\n", success, time_diff_full);

    return 0;
}

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream){
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

size_t clear_data(void* buffer, size_t size, size_t nmemb, void* userp){
	return size * nmemb;
}

char *generate_random_string(int len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *str = malloc((len + 1) * sizeof(char));
    int i;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * 1000000 + tv.tv_usec);
    for (i = 0; i < len; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[len] = '\0';
    return str;
}

int delete_file(const char* path){
    int result = 0;

#if defined(_WIN32)
    result = DeleteFileA(path);
#else
    result = unlink(path);
#endif

    return result;
}

int download_file(const char* node, const char* out_file, const char* user_agent){
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init();
    if (!curl){
        fprintf(stderr, "Failed to initialize curl.\n");
        return 1;
    }

    fp = fopen(out_file, "wb");
    if (!fp){
        fprintf(stderr, "Failed to open output file.\n");
        curl_easy_cleanup(curl);
        return 2;
    }

    curl_easy_setopt(curl, CURLOPT_URL, node);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        fclose(fp);
        curl_easy_cleanup(curl);
        return 3;
    }
    fclose(fp);
    curl_easy_cleanup(curl);

    return 0;
}

int check_internet_connection()
{
    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    #ifdef _WIN32
        WSADATA wsaData;
        int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (err != 0) {
            printf("WSAStartup failed: %d\n", err);
            exit(1);
        }
    #endif

    status = getaddrinfo("www.google.com", "http", &hints, &res);
    if (status != 0) {
        #ifdef _WIN32
            WSACleanup();
        #endif
        return 0;
    }

    freeaddrinfo(res);

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 1;
}


void delay_ms(int milliseconds){
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

long int get_file_size(const char* file_name){
    FILE* fp = fopen(file_name, "rb"); 

    if (fp == NULL) { 
        return EOF;
    }

    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);

    fclose(fp); 
    return size;
}

void parse_config(const char* filename, struct grab_options* gopt) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_BUF_SIZE];
    while (fgets(buf, sizeof(buf), file)) {
        buf[strcspn(buf, "\n")] = '\0';

        char* key = strtok(buf, "=");
        char* value = strtok(NULL, "=");

        if (strcmp(key, "domain") == 0) {
            gopt->domain = strdup(value);
        }
        else if (strcmp(key, "protocol") == 0) {
            gopt->protocol = strdup(value);
            if (strcmp(gopt->protocol, "http") == 0){
                gopt->protocol = "http://";
            }
            if (strcmp(gopt->protocol, "https") == 0){
                gopt->protocol = "https://";
            }
        }
        else if (strcmp(key, "user-agent") == 0) {
            gopt->user_agent = strdup(value);
        }
        else if (strcmp(key, "path") == 0) {
            gopt->path = strdup(value);
            if (strcmp(gopt->path, "default") == 0){
                gopt->path = " ";
            }
            else {
                strcat(gopt->path, "/");
            }
        } 
        else if (strcmp(key, "format") == 0) {
            gopt->format = strdup(value);
        } 
        else if (strcmp(key, "token_length") == 0) {
            gopt->token_length = atoi(value);
        } 
        else if (strcmp(key, "count") == 0) {
            gopt->count = atoi(value);
        } 
        else if (strcmp(key, "debug") == 0) {
            gopt->debug = strcmp(value, "true") == 0 ? 1 : 0;
        }
    }

    fclose(file);
}

void help_menu(void){
    printf("lol");
}
