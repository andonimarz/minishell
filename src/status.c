#include "../libft/libft.h"

extern int	g_status;

int	ft_status(char *str)
{
	if (g_status == 32512)
		g_status = 127;
	if (g_status == 512)
		g_status = 0;
	if (g_status == 256)
		g_status = 1;
	if (ft_strncmp(str, "$?", 2) == 0 && ft_strlen(str) == 2)
	{
		printf("%d: command not found\n", g_status);
		free(str);
		return (0);
	}
	return (1);
}
