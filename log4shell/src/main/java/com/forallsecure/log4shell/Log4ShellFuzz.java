package com.forallsecure.log4shell;

import com.code_intelligence.jazzer.api.FuzzedDataProvider;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Log4ShellFuzz {
  private final static Logger LOGGER = LogManager.getLogger(Log4ShellFuzz.class.getName());

  public static void fuzzerTestOneInput(FuzzedDataProvider data) {
    LOGGER.error(data.consumeRemainingAsString());
  }
}
