/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008 Armin Burgmeier <armin@arbur.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "features.hpp"
#include "core/preferences.hpp"

Gobby::Preferences::User::User(Config::ParentEntry& entry):
	name(entry.get_value<Glib::ustring>("name", Glib::get_user_name())),
	hue(entry.get_value<double>("hue", Glib::Rand().get_double())),
	host_directory(entry.get_value<std::string>("host-directory",
		Glib::build_filename(Glib::get_home_dir(), ".infinote")))
{
}

void Gobby::Preferences::User::serialize(Config::ParentEntry& entry) const
{
	entry.set_value("name", name);
	entry.set_value("hue", hue);
	entry.set_value("host-directory", host_directory);
}

Gobby::Preferences::Editor::Editor(Config::ParentEntry& entry):
	tab_width(entry.get_value<unsigned int>("tab-width", 8)),
	tab_spaces(entry.get_value<bool>("tab-insert-spaces", false)),
	indentation_auto(entry.get_value<bool>("auto-indentation", true)),
	homeend_smart(entry.get_value<bool>("smart-homeend", false) ),
	autosave_enabled(entry.get_value<bool>("autosave-enabled", false) ),
	autosave_interval(
		entry.get_value<unsigned int>("autosave-interval", 10))
{
}

void Gobby::Preferences::Editor::serialize(Config::ParentEntry& entry) const
{
	entry.set_value("tab-width", tab_width);
	entry.set_value("tab-insert-spaces", tab_spaces);
	entry.set_value("auto-indentation", indentation_auto);
	entry.set_value("smart-homeend", homeend_smart);
	entry.set_value("autosave-enabled", autosave_enabled);
	entry.set_value("autosave-interval", autosave_interval);
}

Gobby::Preferences::View::View(Config::ParentEntry& entry):
	wrap_mode(static_cast<Gtk::WrapMode>(entry.get_value<int>(
		"wrap-mode", static_cast<int>(Gtk::WRAP_WORD_CHAR)))),
	linenum_display(entry.get_value<bool>("display-line-numbers", true)),
	curline_highlight(entry.get_value<bool>(
		"highlight-current-line", true)),
	margin_display(entry.get_value<bool>("margin-display", true) ),
	margin_pos(entry.get_value<unsigned int>("margin-position", 80) ),
	bracket_highlight(entry.get_value<bool>(
		"highlight-matching-brackets", true))
{
}

void Gobby::Preferences::View::serialize(Config::ParentEntry& entry) const
{
	entry.set_value("wrap-mode", static_cast<int>(wrap_mode));
	entry.set_value("display-line-numbers", linenum_display);
	entry.set_value("highlight-current-line", curline_highlight);
	entry.set_value("margin-display", margin_display);
	entry.set_value("margin-position", margin_pos);
	entry.set_value("highlight-matching-brackets", bracket_highlight);
}

Gobby::Preferences::Appearance::Appearance(Config::ParentEntry& entry):
	toolbar_style(static_cast<Gtk::ToolbarStyle>(entry.get_value<int>(
		"toolbar-style", static_cast<int>(Gtk::TOOLBAR_BOTH)))),
	font(Pango::FontDescription(entry.get_value<Glib::ustring>(
		"font", "Monospace 10"))),
	userlist_width(entry.get_value<unsigned int>("userlist-width", 150)),
	show_toolbar(entry.get_value<bool>("show-toolbar", true)),
	show_statusbar(entry.get_value<bool>("show-statusbar", true)),
	show_browser(entry.get_value<bool>("show-browser", true)),
	show_userlist(entry.get_value<bool>("show-userlist", true))
{
}

void Gobby::Preferences::Appearance::
	serialize(Config::ParentEntry& entry) const
{
	entry.set_value("toolbar-style", static_cast<int>(toolbar_style) );

	entry.set_value(
		"font",
		static_cast<const Pango::FontDescription&>(font).to_string());

	entry.set_value("userlist-width", userlist_width);

	entry.set_value("show-toolbar", show_toolbar);
	entry.set_value("show-statusbar", show_statusbar);
	entry.set_value("show-browser", show_browser);
	entry.set_value("show-userlist", show_userlist);
}

Gobby::Preferences::Security::Security(Config::ParentEntry& entry):
	trust_file(entry.get_value<std::string>("trust-file", "")),
	policy(static_cast<InfXmppConnectionSecurityPolicy>(
		entry.get_value<int>("policy", static_cast<int>(
			INF_XMPP_CONNECTION_SECURITY_BOTH_PREFER_TLS))))
{
}

void Gobby::Preferences::Security::serialize(Config::ParentEntry& entry) const
{
	entry.set_value("trust-file", trust_file);
	entry.set_value("policy", static_cast<int>(policy));
}

Gobby::Preferences::Preferences(Config& config):
	user(config.get_root()["user"]),
	editor(config.get_root()["editor"]),
	view(config.get_root()["view"]),
	appearance(config.get_root()["appearance"]),
	security(config.get_root()["security"])
{
}

void Gobby::Preferences::serialize(Config& config) const
{
	// Serialise into config
	user.serialize(config.get_root()["user"]);
	editor.serialize(config.get_root()["editor"]);
	view.serialize(config.get_root()["view"]);
	appearance.serialize(config.get_root()["appearance"]);
	security.serialize(config.get_root()["security"]);
}

