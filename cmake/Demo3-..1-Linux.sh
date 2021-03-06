#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --version         print cmake installer version
  --prefix=dir      directory in which to install
  --include-subdir  include the Demo3-..1-Linux subdirectory
  --exclude-subdir  exclude the Demo3-..1-Linux subdirectory
  --skip-license    accept license
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "Demo3 Installer Version: ..1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
The MIT License (MIT)

Copyright (c) 2013 Joseph Pan(http://hahack.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the Demo3 will be installed in:"
    echo "  \"${toplevel}/Demo3-..1-Linux\""
    echo "Do you want to include the subdirectory Demo3-..1-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/Demo3-..1-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

extractor="pax -r"
command -v pax > /dev/null 2> /dev/null || extractor="tar xf -"

tail $use_new_tail_syntax +167 "$0" | gunzip | (cd "${toplevel}" && ${extractor}) || cpack_echo_exit "Problem unpacking the Demo3-..1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� �/[ �Z}pT����nvC�f����<+Q�f�I6�� �I^0��bkx���ُ��[�H'ʰEl��:Lk�[u������J:�8��1�v(�NPP�dZa{�{����6љ�x{���s��|��{���D���p8��p�C��*46776/v�4�9Gc���\��n�tJ�I�)R2)��7Q9ݹ��������լc��ojv5�濩e1��&gS3�W�Q�����Ao�*�ar2nH:fv+��C7�m�`	(������ʦ=7pk�vM���e��V���n���g
�I���?Q4 .g��
��n�����Y���j�]�'�n�	�F|�`=�_��c��}Dݧ� ��LQ����;�����ڕ�/N6����J� �9���X��r6Ă��h"=P?��U�r�SI{��&�]��7g����6Wu����S/��.:�h�����xǀg�s�PY�3�kȶ�n�.��S���7y&�Z�o������N=v�T�p�����y��&�������9�>�����h��>��Go�'=ե
@f^K����;K��J�����-%��*��𳦄�� ��,�ѶY���q������f
���X�uxM�^�d�����
��U\���0N���?����}�����E���W �Ch?ַ�����s��S�� ��8Z�. t�t	AQ�є,J=]m�dB���c"�p<�лD ��*��zm1_*%�Ts]���6TM@��?-�@�M�!����OV�4pq_4A�@*-��	�!}�����u�.M�,4��XL ПJa�՝�mB���ނG�3�QB�̸��瞃Wzv�=��aD���w�r6W>V��+�#��_���\0W���P�/(���� /|,)��Ow^^��g-�^ӟ,��M��)��-���l�+�([��[5�zΜ�B�{�h��S�"u�̈"�G2�ҙ��1$���V�� u�̐"7A94D��x�#s|�9���BwOǑ���#у�9����_B��BU����Uv���G�?8f�3��־��voZ�T�=�R��B�
ى��F���+^1@|�pt%��_�g�UoU���]+��9���B��lX�a��b>Uj:`����i�G�C����� {���h���̸3|�g����}�&~�������1P,G��;�����R�(jGFX�v���\f�e��,�={�6�j�f�Xu~䓪�޳P�B�j�Qht��*�����?c�ۛS˼�S<�����g�a�P�8�\�_�]�;=�����ӹ�n��������K��;o=��Ƀ��t�?|N��'.:3vf.�C����C����h�~��s��ϳ�#�W��!���f�Sכ��e\]���R"'�í+!sS@"���;w�D�'9��H>i;���&�.�ES\]�2L�a�?{��g�� ���vC�	׳�Y�3y�g!��@��kf�z�ؘ�J�e�1��bC�A����UU�Ͱ�~�`���֬���f�V�^��y�� �A1ٯ�_�]��v�mS�أГZ����f��j�}�m��<j�Z�}�V�GL�ձ���.4wYݒu����X�Z9��[���/�k�)��&i��%�i愘<�y%�$���e?�"��9���|4�ȸ|U��+Y%'���#�lΤ��]=���q	�sr���|&�R.f��y��)�GH,r=��en�ˤݤ�rJ�����g�L꽀�ٸ�Z9�����ݘ?��/0�-_Z�ֶ�[��O'�4�bw����"5�lt�N��[U�kr�t�c)�: 㡎&�Cb<��U�8P�z��ŌbZ��t"ƚC�h^��ek��d�	���dR��z,��ث`&�ҡ81>�HFd�E�a��t����2�-����u�=�H��m^���U���? �zU��7�4W-����Ә:�
���:��n��u���Av���4V�ێ��vf�,�uY�r("w͓��XRfg�5;5�rDc�rT)��T�����4D�q�a �M�6�uww�_��������@+t\��RΒa1ؘ�a���EKߏ����w�,tOFaN�A�0�o�$��O'R�pB*�(X9$�I@S���4:w��p`\���HR��ޡ�V�%}2.E 	�PZ�k[��Z�\}\N'�a1!J� }R �B͝p�a�?�s��\}�T�-��RRrR�O��"HEw���~r^�p�I>M���<�7 Y7��a-n���Z�,�Okq���f��;�����W->%�k���W�n]|*����-��P�|~C�O�����t0������4xu�=��g�.~��n�o1r���5���/��xqF�k�0�S�[��>��ah�1��Y�Tʊ��+,zyPqP-��n�87�+���C��}�<��~�)?�����L�~���J�t0T����P���wFQ��S����z8�����c���'��祚Q���S��u�b��{����[�~�����Q��nF?��f���J��I	���qF?O���=���c?g��o�|ﻌ~������ְ�yڹ�~;Y�����/c��  �)9
�@ִ�:;6��'r9.P66���I!K�}1!_�)�� �d�?&�bо�e�S_I��
>I�m`  m!��`:�M
$%��Q%a� �Z���
޵�(��4��k�P�6�J
_"����w��tu�i�p
X�����k�}=�z�ڈ�՝�Z=�ºU�6x{�Ok�W(�-���F�j��0s���Z�լ���?��ҥ3�tqa~�J�O��.�t�)t�4=ʶS5�L�{j{\��!�%�G��(�{�ovOkG��c)�H���h,XE��R`nO@*�%�d�(��ɄF`�$�|H��è֮t���Ix#��W�?��T&�.F�J�������F� ��$�=�x4 �[�&�M`�GE����O���/�È�h"�������H�hB$����#B�k�*!�~��ʪLG"%��k���V�9J�Hɍ�=��e̟�����$�'q�S��$bZB�X�wSD$>���Q���y�;��!�$��p�$�B��M@�m{���	;�~���`Ps%D&�ۻA��,(�?������a�'��Ǐ�a�V,�s�0�'�!�����<�����8aD�^����P���ҍ��)}ş����f���E�?������o���6�~Fٓ��'��)}�����K�ۯ���e�>���*;)}�� eO�i���3J��7�����s�S������*�'������ؓ�����	Թ#���]T�|�B�ؓu�U?9o�U�_?��)�\|�+�'���I\�۴���	]��'q�F��>����]#������L�OD�`{�/�[[�����HҺ������-��R�~��{J������'5� �iN5tN���g��Ff���� ��78zy��O����r�7Vג��@,��7�_���&��q���kAd��D(�G&������t�3�͹�ollr��w:\���^jX�ݔN�׻�+t����ṅS&���I��I���2�b}� 6  