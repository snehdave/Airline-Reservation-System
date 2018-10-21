#! /bin/sh
# Run this to generate all the initial makefiles, etc.
#
# Set CONFIG_ARGS to the argument list you wish to pass to configure.

set -eu

PQXXVERSION=$(./tools/extract_version)
PQXX_ABI=$(./tools/extract_version --abi)
PQXX_MAJOR=$(./tools/extract_version --major)
PQXX_MINOR=$(./tools/extract_version --minor)
echo "libpqxx version $PQXXVERSION"
echo "libpqxx ABI version $PQXX_ABI"

substitute() {
	sed -e "s/@PQXXVERSION@/$PQXXVERSION/g" \
		-e "s/@PQXX_MAJOR@/$PQXX_MAJOR/g" \
		-e "s/@PQXX_MINOR@/$PQXX_MINOR/g" \
		-e "s/@PQXX_ABI@/$PQXX_ABI/g" \
		"$1"
}

# Generate version header.
substitute include/pqxx/version.hxx.template >include/pqxx/version.hxx

# Generate Windows makefiles.
# Add carriage returns to turn them into MS-DOS format.
makewinmake() {
	./tools/template2mak.py "$1" | tr -d '\r' | sed -e 's/$/\r/' >"$2"
}


# Use templating system to generate various Makefiles.
for output in test/Makefile.am test/unit/Makefile.am
do
	./tools/template2mak.py $output.template $output
done
for output in vc-libpqxx vc-test vc-test-unit MinGW
do
	makewinmake win32/$output.mak.template win32/$output.mak
done

autoheader
libtoolize --force --automake --copy
aclocal -I . -I config/m4
automake --verbose --add-missing --copy
autoconf

conf_flags="--enable-maintainer-mode ${CONFIG_ARGS:-}"
if [ -z "${NOCONFIGURE:-}" ]
then
	echo Running ./configure $conf_flags "$@" ...
	./configure $conf_flags "$@"
	echo "Now type 'make' to compile libpqxx."
else
	echo Skipping configure process.
fi
