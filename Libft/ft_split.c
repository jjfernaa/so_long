/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:40:28 by juan-jof          #+#    #+#             */
/*   Updated: 2024/12/18 04:29:25 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*extract_word(char const *s, char c, size_t *start)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[*start] && s[*start] == c)
		(*start)++;
	while (s[*start + len] && s[*start + len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + *start, len + 1);
	*start += len;
	return (word);
}

static void	free_array(char **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;
	size_t	start;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < word_count)
	{
		result[i] = extract_word(s, c, &start);
		if (!result[i])
		{
			free_array(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

/* int	main(void)
{
	char	*str;
	char	**result;
	size_t	i;

	str = "Hello, Malaga, 42";
	result = ft_split(str, ',');
	i = 0;
	while (result[i] != NULL)
		i++;
	
	printf("Palabra 1 = %s\n", result[0]);
	printf("Palabra 2 = %s\n", result[1]);
	printf("Palabra 3 = %s\n", result[2]);
	free_array(result, i);
	return (0);
} */