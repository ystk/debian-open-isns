die()
{
  echo "$@" >&2
  exit 1
}

service_status()
{
  if [ x"$1" = x"NOFAIL" ] ; then
    shift
    _R=":"
  else
    _R="die FAILURE"
  fi
  for service in "$@" ; do
    echo "Status of ${service}:"
    service "${service}" status || ${_R}
    if [ -d /run/systemd/system ] ; then
      echo "Journal log of ${service}:"
      journalctl -u "${service}".service || ${_R}
    fi
  done
}
