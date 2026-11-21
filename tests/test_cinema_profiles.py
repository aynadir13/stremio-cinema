"""Native profile directory isolation: compile the REAL profile C module."""
import os
import pathlib
import subprocess
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
HARNESS = r"""
#include "core/cinema_profile.h"
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv) {
  if(argc==4 && !strcmp(argv[2],"set")) return cinema_profile_set_active(argv[1],argv[3])?0:2;
  if(argc!=2)return 3;
  const char* d=cinema_profile_data_dir(argv[1]);
  if(!d)return 2;
  puts(d);
  return 0;
}
"""

class ProfileDirectoryTests(unittest.TestCase):
    def test_process_profiles_are_separate_and_invalid_ids_fail_closed(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=pathlib.Path(tmp)
            source=p/"harness.c"
            exe=p/"profile-check"
            source.write_text(HARNESS)
            cc=subprocess.run(["cc","-std=c11","-Wall","-Wextra","-Werror",
                               "-I",str(ROOT/"src"),
                               str(ROOT/"src/core/cinema_profile.c"),str(source),"-o",str(exe)],
                              capture_output=True,text=True)
            self.assertEqual(cc.returncode,0,cc.stderr)
            def run(id):
                env=dict(os.environ)
                env.pop("SB_CINEMA_PROFILE",None)
                if id is not None:env["SB_CINEMA_PROFILE"]=id
                return subprocess.run([str(exe),str(p)],env=env,capture_output=True,text=True)
            legacy=run(None)
            alice=run("alice")
            bob=run("bob")
            self.assertEqual(legacy.returncode,0)
            self.assertEqual(alice.returncode,0)
            self.assertEqual(bob.returncode,0)
            self.assertEqual(legacy.stdout.strip(),str(p))
            self.assertNotEqual(alice.stdout,bob.stdout)
            self.assertEqual(alice.stdout.strip(),str(p/"profiles/alice"))
            self.assertEqual(bob.stdout.strip(),str(p/"profiles/bob"))
            for name in ("alice","bob"):
                self.assertTrue((p/"profiles"/name).is_dir())
                self.assertEqual((p/"profiles"/name).stat().st_mode & 0o777,0o700)
            for bad in ("../oops","../../etc/passwd","a/b","test space","."*33):
                self.assertNotEqual(run(bad).returncode,0,bad)
            self.assertFalse((p/"oops").exists())
            def activate(name):
                env=dict(os.environ)
                env.pop("SB_CINEMA_PROFILE",None)
                return subprocess.run([str(exe),str(p),"set",name],env=env,capture_output=True,text=True)
            self.assertEqual(activate("sam").returncode,0)
            self.assertEqual(run(None).stdout.strip(),str(p/"profiles/sam"))
            self.assertEqual(run("bob").stdout.strip(),str(p/"profiles/bob"))
            self.assertEqual((p/"cinema-active-profile").stat().st_mode & 0o777,0o600)
            self.assertNotEqual(activate("../../escape").returncode,0)
            self.assertEqual(run(None).stdout.strip(),str(p/"profiles/sam"))
            self.assertEqual(activate("default").returncode,0)
            self.assertEqual(run(None).stdout.strip(),str(p))
if __name__=="__main__":unittest.main()
