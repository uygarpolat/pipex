/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:12:17 by upolat            #+#    #+#             */
/*   Updated: 2024/05/05 20:46:57 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

// ft_printf.c
int		ft_printf(const char *str, ...);
int		caster(va_list *arg, const char c);

// ft_printf_types.c
int		print_d_i(int d);
int		print_s(char *s);
int		print_c(char c);
int		print_u(unsigned int d);
int		print_p_x(void *voidstr, const char c);

// ft_printf_utils.c
int		ft_putchar_fd_int(char c, int fd);
char	*ft_utoa(unsigned int d);

// ft_printf_base.c
int		ft_putnbr_base_unsigned(uintptr_t nb, char *base);

#endif
