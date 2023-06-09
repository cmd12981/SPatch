int
__archive_pathmatch(const char *p, const char *s, int flags)
{
	/* Empty pattern only matches the empty string. */
	if (p == NULL || *p == '\0')
		return (s == NULL || *s == '\0');
	else if (s == NULL)
		return (0);

	/* Leading '^' anchors the start of the pattern. */
	if (*p == '^') {
		++p;
		flags &= ~PATHMATCH_NO_ANCHOR_START;
	}

	if (*p == '/' && *s != '/')
		return (0);

	/* Certain patterns anchor implicitly. */
	if (*p == '*' || *p == '/') {
		while (*p == '/')
			++p;
		while (*s == '/')
			++s;
		return (pm(p, s, flags));
	}

	/* If start is unanchored, try to match start of each path element. */
	if (flags & PATHMATCH_NO_ANCHOR_START) {
		for ( ; s != NULL; s = strchr(s, '/')) {
			if (*s == '/')
				s++;
			if (pm(p, s, flags))
				return (1);
		}
		return (0);
	}

	/* Default: Match from beginning. */
	return (pm(p, s, flags));
}
