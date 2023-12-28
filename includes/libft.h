/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:49:13 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/27 13:32:57 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define CHAR_BIT 8
# define SCHAR_MIN -128
# define SCHAR_MAX +127
# define UCHAR_MAX 255
# define CHAR_MIN -128
# define CHAR_MAX +127
# define MB_LEN_MAX 16
# define SHRT_MIN -32768
# define SHRT_MAX +32767
# define USHRT_MAX 65535
# define INT_MAX +2147483647
# define INT_MIN -2147483648
# define UINT_MAX 4294967295
# define LONG_MIN -9223372036854775808
# define LONG_MAX +9223372036854775807
# define ULONG_MAX 18446744073709551615

//////////////////////////////////////////////////////////////////////////////

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);

char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, unsigned int nb);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *src);
char				*ft_strrchr(const char *str, int c);
char				*ft_strnstr(const char *str, const char *ndl, size_t len);

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *str, char c);
char				*ft_itoa(int n);
char				*ft_strtoupper(char *str);
char				*ft_strtolower(char *str);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

//////////////////////////////////////////////////////////////////////////////

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_lstsize(t_list *lst);

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

//////////////////////////////////////////////////////////////////////////////

int					ft_printf(const char *str, ...);
int					ft_format(va_list args, const char format);
int					ft_print_percent(void);
int					ft_print_char(int str);
int					ft_print_str(char *str);
int					ft_print_nbr(int nbr);
int					ft_print_ptr(unsigned long long ptr);
int					ft_print_hex(unsigned int nbr, const char format);
int					ft_print_unsigned(unsigned int nbr);

int					ft_printf_len(uintptr_t nbr);
int					ft_num_len(unsigned int nbr);

void				ft_put_str(char *str);
void				ft_put_ptr(uintptr_t nbr);
void				ft_put_hex(unsigned int nbr, const char format);

char				*ft_unsigned_itoa(unsigned int nbr);

//////////////////////////////////////////////////////////////////////////////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 2048
# endif

char				*get_next_line(int fd);
char				*ft_gnl_strjoin(char *s1, char *s2);

#endif
