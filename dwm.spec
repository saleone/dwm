%define debug_package %{nil}

Name: dwm 
Version: 6.1
Release: 1%{?dist}
Summary: dwm is an extremely fast, small, and dynamic window manager for X

License: MIT
URL: https://github.com/saleone/dwm
Source0: https://github.com/saleone/dwm/archive/%{version}.tar.gz
Source3: %{name}.desktop

BuildRequires: gcc
BuildRequires: fontconfig-devel
BuildRequires: libX11-devel
BuildRequires: libXft-devel
BuildRequires: libXinerama-devel

Requires: st
Requires: dmenu
Requires: slock


%description
%{summary}


%prep
%autosetup

%build
%make_build


%install
%make_install
mkdir -p %{buildroot}/usr/share/xsessions
install -m644 %{SOURCE3} %{buildroot}/usr/share/xsessions/dwm.desktop


%files
/usr/local/bin/dwm
/usr/local/share/man/man1/dwm.1
/usr/share/xsessions/dwm.desktop


%changelog
* Sat Apr 6 2019 Saša Savić <sasa@sasa-savic.com> 6.1-1
- Initial RPM release

