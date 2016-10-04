/*
 * Copyright 2016 Jonathan Eyolfson
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include <wayland-server.h>
#include <compositor.h>
#include <libweston-desktop.h>

static void surface_added(struct weston_desktop_surface *surface,
                          void *user_data)
{
}

static void surface_removed(struct weston_desktop_surface *surface,
                            void *user_data)
{
}

static bool resources_allocate(struct wl_display **wl_display,
                               struct weston_compositor **weston_compositor,
                               struct weston_desktop **weston_desktop)
{
	*wl_display = wl_display_create();
	if (*wl_display == NULL) {
		return false;
	}

	*weston_compositor = weston_compositor_create(*wl_display, NULL);
	if (*weston_compositor == NULL) {
		wl_display_destroy(*wl_display);
		return false;
	}

	struct weston_desktop_api weston_desktop_api = {
		.surface_added = surface_added,
		.surface_removed = surface_removed,
	};
	*weston_desktop = weston_desktop_create(*weston_compositor,
	                                        &weston_desktop_api,
	                                        NULL);
	if (*weston_desktop == NULL) {
		weston_compositor_destroy(*weston_compositor);
		wl_display_destroy(*wl_display);
		return false;
	}

	return true;
}

static void resources_deallocate(struct wl_display *wl_display,
                                 struct weston_compositor *weston_compositor,
                                 struct weston_desktop *weston_desktop)
{
	weston_desktop_destroy(weston_desktop);
	weston_compositor_destroy(weston_compositor);
	wl_display_destroy(wl_display);
}

int main()
{
	printf("eyl Desktop 0.0.1-development\n");

	struct wl_display *wl_display;
	struct weston_compositor *weston_compositor;
	struct weston_desktop *weston_desktop;

	if (!resources_allocate(&wl_display,
	                        &weston_compositor,
	                        &weston_desktop)) {
		return 1;
	}

	resources_deallocate(wl_display, weston_compositor, weston_desktop);
	return 0;
}
