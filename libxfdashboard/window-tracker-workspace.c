/*
 * window-tracker-workspace: A workspace tracked by window tracker and
 *                           also a wrapper class around WnckWorkspace.
 *                           By wrapping libwnck objects we can use a 
 *                           virtual stable API while the API in libwnck
 *                           changes within versions. We only need to
 *                           use #ifdefs in window tracker object and
 *                           nowhere else in the code.
 * 
 * Copyright 2012-2016 Stephan Haller <nomad@froevel.de>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <libxfdashboard/window-tracker-workspace.h>

#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#include <libwnck/libwnck.h>

#include <glib/gi18n-lib.h>

#include <libxfdashboard/window-tracker.h>
#include <libxfdashboard/marshal.h>
#include <libxfdashboard/compat.h>


/* Usually we found define a class in GObject system here but
 * this class is a wrapper around WnckWorkspace to create a virtual stable
 * libwnck API regardless of its version.
 */

/* IMPLEMENTATION: Public API */

/* Return type of WnckWorkspace as our type */
GType xfdashboard_window_tracker_workspace_get_type(void)
{
	return(WNCK_TYPE_WORKSPACE);
}

/* Check if both workspaces are the same */
gboolean xfdashboard_window_tracker_workspace_is_equal(XfdashboardWindowTrackerWorkspace *inLeft,
														XfdashboardWindowTrackerWorkspace *inRight)
{
	gint			leftIndex, rightIndex;

	g_return_val_if_fail(WNCK_IS_WORKSPACE(inLeft), FALSE);
	g_return_val_if_fail(WNCK_IS_WORKSPACE(inRight), FALSE);

	/* Check if both are the same workspace or refer to same one */
	leftIndex=xfdashboard_window_tracker_workspace_get_number(inLeft);
	rightIndex=xfdashboard_window_tracker_workspace_get_number(inRight);
	if(inLeft==inRight || leftIndex==rightIndex) return(TRUE);

	/* If we get here then they cannot be considered equal */
	return(FALSE);
}

/* Get number of workspace */
gint xfdashboard_window_tracker_workspace_get_number(XfdashboardWindowTrackerWorkspace *inWorkspace)
{
	g_return_val_if_fail(WNCK_IS_WORKSPACE(inWorkspace), -1);

	return(wnck_workspace_get_number(WNCK_WORKSPACE(inWorkspace)));
}

/* Get name of workspace */
const gchar* xfdashboard_window_tracker_workspace_get_name(XfdashboardWindowTrackerWorkspace *inWorkspace)
{
	g_return_val_if_fail(WNCK_IS_WORKSPACE(inWorkspace), NULL);

	return(wnck_workspace_get_name(WNCK_WORKSPACE(inWorkspace)));
}

/* Get size of workspace */
gint xfdashboard_window_tracker_workspace_get_width(XfdashboardWindowTrackerWorkspace *inWorkspace)
{
	g_return_val_if_fail(WNCK_IS_WORKSPACE(inWorkspace), 0);

	return(wnck_workspace_get_width(WNCK_WORKSPACE(inWorkspace)));
}

gint xfdashboard_window_tracker_workspace_get_height(XfdashboardWindowTrackerWorkspace *inWorkspace)
{
	g_return_val_if_fail(WNCK_IS_WORKSPACE(inWorkspace), 0);

	return(wnck_workspace_get_height(WNCK_WORKSPACE(inWorkspace)));
}

void xfdashboard_window_tracker_workspace_get_size(XfdashboardWindowTrackerWorkspace *inWorkspace,
													gint *outWidth,
													gint *outHeight)
{
	gint		width, height;

	g_return_if_fail(WNCK_IS_WORKSPACE(inWorkspace));

	/* Get width and height of workspace */
	width=wnck_workspace_get_width(WNCK_WORKSPACE(inWorkspace));
	height=wnck_workspace_get_height(WNCK_WORKSPACE(inWorkspace));

	/* Set values */
	if(outWidth) *outWidth=width;
	if(outHeight) *outHeight=height;
}

/* Activate workspace */
void xfdashboard_window_tracker_workspace_activate(XfdashboardWindowTrackerWorkspace *inWorkspace)
{
	g_return_if_fail(WNCK_IS_WORKSPACE(inWorkspace));

	wnck_workspace_activate(WNCK_WORKSPACE(inWorkspace), xfdashboard_window_tracker_get_time());
}
