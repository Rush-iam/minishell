/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:24:33 by ngragas           #+#    #+#             */
/*   Updated: 2021/11/01 22:34:41 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isspace(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_ptr_malloc(void **ptr, size_t size);
void			*ft_ptr_assign(void **dst_ptr, void *src_ptr);
void			*ft_ptr_free(void *ptr);
size_t			ft_ptr_array_len(void **ptr_array);
void			*ft_ptr_array_free(void **array);
void			*ft_ptr_array_nfree(void **array, size_t count);

void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);

char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_chr(char const *s1, char const *s2, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);

int				ft_atoi(const char *str);
char			*ft_itoa(int n);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstinsert(t_list **lst, t_list *new);
void			*ft_lstpop(t_list **lst);
t_list			*ft_lstpopconv(t_list **lst, void *(*f)(void *));
t_list			*ft_lstpopconv_xd(t_list **lst,
					void *(*f)(void *, void *), void *extra_data);
t_list			*ft_lstdetach(t_list **lst, t_list *detachable_link);
void			ft_lstremove(t_list **begin, t_list *to_delete);
void			ft_lstremoveif(t_list **begin, void *data_ref, int (*cmp)(), \
								void (*free_fct)(void *));
void			ft_lstsort(t_list **lst, int (*cmp)());
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstreverse(t_list **begin_list);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstiterix(t_list *lst, void (*f)(void *, int, int));
void			ft_lststream(t_list **lst, t_list *(*pipeline)(t_list **));
void			ft_lststream_xd(t_list **lst,
					t_list *(*pipeline)(t_list **, void *), void *extra_data);
void			ft_lstpipeline(t_list **lst, t_list *(*pipeline)(t_list *));
void			ft_lstpipeline_xd(t_list **lst,
					t_list *(*pipeline)(t_list *, void *), void *extra_data);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
							void (*del)(void *));
t_list			*ft_lstconv(t_list *lst, void *(*f)(void *));
t_list			*ft_lstconv_xd(t_list *lst,
					void *(*f)(void *, void *), void *extra_data);
void			*ft_lstreduce(t_list *lst, void *initial, \
							void *(*f)(void *, void *));
void			*ft_lstpopreduce(t_list **lst, void *initial, \
							void *(*f)(void *, void *));
void			**ft_lst_to_ptr_array(t_list **list);

int				ft_wchrto8(char *dst_utf8, wchar_t src_utf32);
size_t			ft_wstrto8(char *dst_utf8, const wchar_t *src_utf32, size_t n);
ssize_t			ft_write(int fd, const void *buf, size_t size);

int				ft_min(int a, int b);
int				ft_max(int a, int b);
unsigned int	ft_umin(unsigned a, unsigned b);
unsigned int	ft_umax(unsigned a, unsigned b);

int				ft_file_exists(char *path);
char			*ft_basename(char *path);

#endif
