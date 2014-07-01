cd doc
if ERRORLEVEL goto end
xsltproc c:\docbook-xsl-1.70.1\fo\docbook.xsl modassert.xml > modassert.fo
call "c:\ProgramFiles\fop-1.0\fop.bat" modassert.fo modassert.pdf

rem requires Cygwin
chmod 666 modassert.pdf

cd ..

:end
