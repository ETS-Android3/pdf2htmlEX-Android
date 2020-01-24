/*
 * pdf2htmlEX.h
 *
 * Copyright (C) 2012-2015 Lu Wang <coolwanglu@gmail.com>
 * Copyright (C) 2020 Vilius Sutkus'89 <ViliusSutkus89@gmail.com>
 *
 * pdf2htmlEX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <exception>
#include <memory>

namespace pdf2htmlEX {

  class Param;

  class pdf2htmlEX {
  private:
    std::unique_ptr<Param> param;
    std::string m_tmpDirWithoutSuffix;

    void initParam();
    void checkParam();

    void prepareDirectories();

  public:
    pdf2htmlEX();

    virtual ~pdf2htmlEX();

    void convert();

    pdf2htmlEX &setInputFilename(const std::string &inputFilename);

    pdf2htmlEX &setOutputFilename(const std::string &outputFilename);

    pdf2htmlEX &setFirstPage(int firstPage);

    pdf2htmlEX &setLastPage(int lastPage);

    pdf2htmlEX &setZoomRatio(double zoomRatio);

    pdf2htmlEX &setFitWidth(double fitWidth);

    pdf2htmlEX &setFitHeight(double fitHeight);

    pdf2htmlEX &setUseCropBox(bool useCropBox);

    pdf2htmlEX &setDPI(double desiredDPI);

    pdf2htmlEX &setEmbedCSS(bool embedCSS);

    pdf2htmlEX &setEmbedFont(bool embedFont);

    pdf2htmlEX &setEmbedImage(bool embedImage);

    pdf2htmlEX &setEmbedJavascript(bool embedJavascript);

    pdf2htmlEX &setEmbedOutline(bool embedOutline);

    pdf2htmlEX &setSplitPages(bool split_pages);

    pdf2htmlEX &setDestinationDir(const std::string &destinationDir);

    pdf2htmlEX &setCSSFilename(const std::string &cssFilename);

    pdf2htmlEX &setPageFilename(const std::string &pageFilename);

    pdf2htmlEX &setOutlineFilename(const std::string &outlineFilename);

    //render graphics in addition to text
    pdf2htmlEX &setProcessNonText(bool processNonText);

    pdf2htmlEX &setProcessOutline(bool processOutline);

    pdf2htmlEX &setProcessAnnotation(bool processAnnotation);

    pdf2htmlEX &setProcessForm(bool processForm);

    pdf2htmlEX &setPrinting(bool printing);

    pdf2htmlEX &setFallback(bool fallback);

    pdf2htmlEX &setTmpFileSizeLimit(int tmpFileSizeLimit);

    pdf2htmlEX &setEmbedExternalFont(bool embedExternalFont);

    pdf2htmlEX &setFontFormat(const std::string &fontFormat = "woff");

    pdf2htmlEX &setDecomposeLigature(bool decomposeLigature);

    pdf2htmlEX &setAutoHint(bool autoHint);

    //external tool for hinting fonts (overrides --auto-hint)
    pdf2htmlEX &setExternalHintTool(const std::string &externalHintTool);

    //stretch narrow glyphs instead of padding them
    pdf2htmlEX &setStretchNarrowGlyph(bool stretchNarrowGlyph);

    //shrink wide glyphs instead of truncating them
    pdf2htmlEX &setSqueezeWideGlyph(bool squeezeWideGlyph);

    //clear the fstype bits in TTF/OTF fonts
    pdf2htmlEX &setOverrideFstype(bool overrideFSType);

    //convert Type 3 fonts for web (experimental)
    pdf2htmlEX &setProcessType3(bool processType3);

    pdf2htmlEX &setHorizontalEpsilon(double horizontalEpsilon);

    pdf2htmlEX &setVEpsilon(double verticalEpsilon);

    pdf2htmlEX &setSpaceThreshold(double spaceThreshold);

    pdf2htmlEX &setFontSizeMultiplier(double fontSizeMultiplier);

    pdf2htmlEX &setSpaceAsOffset(bool spaceAsOffset);

    // how to handle ToUnicode CMaps (0=auto, 1=force, -1=ignore)
    pdf2htmlEX &setToUnicode(int toUnicode);

    // try to reduce the number of HTML elements used for text
    pdf2htmlEX &setOptimizeText(bool optimizeText);

    // 0: Don't do text visibility checks.
    // 1: Fully occluded text handled.
    // 2: Partially occluded text handled
    pdf2htmlEX &setCorrectTextVisibility(int correctTextVisibility);

    // Rendering DPI to use if correctTextVisibility == 2 and there is partially covered text on the page
    pdf2htmlEX &setCoveredTextDPI(double coveredTextDPI);

    pdf2htmlEX &setBackgroundImageFormat(const std::string &backgroundImageFormat = "png");

    // if node count in a svg background image exceeds this limit,
    // fall back this page to bitmap background; negative value means no limit
    pdf2htmlEX &setSVGNodeCountLimit(int SVGNodeCountLimit);

    // 1: embed bitmaps in svg background;
    // 0: dump bitmaps to external files if possible
    pdf2htmlEX &setSVGEmbedBitmap(int SVGEmbedBitmap);

    pdf2htmlEX &setOwnerPassword(const std::string &ownerPassword);

    pdf2htmlEX &setUserPassword(const std::string &userPassword);

    pdf2htmlEX &setDRM(bool enableDRM);

    pdf2htmlEX &setCleanTMPAfterConversion(bool cleanTMP);

    pdf2htmlEX &setTMPDir(const std::string &TMPDir);

    pdf2htmlEX &setDataDir(const std::string &dataDir);

    pdf2htmlEX &setPopplerDataDir(const std::string &popplerDataDir);

    pdf2htmlEX &setDebug(bool debug);

    // texts are drawn on both text layer and background for proof
    pdf2htmlEX &setProof(bool proof);

    pdf2htmlEX &setQuiet(bool quiet);
  };

  class ConversionFailedException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  class DocumentCopyProtectedException : public ConversionFailedException {
    using ConversionFailedException::ConversionFailedException;
  };

  class EncryptionPasswordException : public ConversionFailedException {
    using ConversionFailedException::ConversionFailedException;
  };

} // namespace pdf2htmlEX