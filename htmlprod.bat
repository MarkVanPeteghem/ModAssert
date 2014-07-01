cd doc
if ERRORLEVEL goto end
rm -f *.html

xsltproc --stringparam html.stylesheet style.css c:\docbook-xsl-1.70.1\html\chunk.xsl modassert.xml
chmod 666 *.html

set LYNX_CFG=C:\Program Files (x86)\Lynx\lynx.cfg

xsltproc --stringparam rootid "changelog" c:\docbook-xsl-1.70.1\html\docbook.xsl modassert.xml > changelog.html
lynx -dump changelog.html > ChangeLog
chmod 666 ChangeLog
del changelog.html
unix2dos ChangeLog
cp ChangeLog ..\NEWS
mv ChangeLog ..

xsltproc --stringparam rootid "readme" c:\docbook-xsl-1.70.1\html\docbook.xsl modassert.xml > readme.html
lynx -dump readme.html > README
chmod 666 README
del readme.html
unix2dos README
mv README ..

cd ..
:end
