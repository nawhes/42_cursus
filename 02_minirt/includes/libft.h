/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nawhes <sehpark@student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 01:21:18 by nawhes            #+#    #+#             */
/*   Updated: 2021/01/24 06:43:37 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include <stdint.h>

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

/*
** tools
*/

int						ft_atoi(const char *nptr);
double					ft_atof(const char *nptr);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_isspace(int c);
char					*ft_itoa(int n);
char					*ft_itoa_base(int n, char *base);
char					*ft_lltoa(long long n);
char					*ft_uitoa(unsigned int n);
char					*ft_uitoa_base(unsigned int n, char *base);
char					*ft_ulltoa(unsigned long long n);
char					*ft_ulltoa_base(unsigned long long n, char *base);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_to_utf8(wint_t c);
int						free_all(char **p1, char **p2);

/*
** string
*/

char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strdup(const char *s);
char					*ft_strndup(const char *s, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
char					*ft_strcpy(char *dest, const char *src);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strmapi(char const *s,
									char (*f)(unsigned int, char));
int						ft_strncmp(const char *s1, const char *s2,
									size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
									size_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, unsigned int start,
									size_t len);
char					*ft_strpbrk(const char *string, const char *control);

/*
** list
*/

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
									void (*del)(void *));

/*
** memory
*/

void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
void					*ft_memccpy(void *dest, const void *src, int c,
									size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);

/*
** io
*/

int						ft_putchar_fd(char c, int fd);
int						ft_putstr_fd(char *s, int fd);
int						ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
int						ft_putwchar_fd(wint_t c, int fd);

#endif
